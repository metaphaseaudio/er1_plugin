//
// Created by Mattb on 6/20/2022.
//

#include "GlobalCtrls.h"
#include "../look_and_feel/StandardShapes.h"
#include "../fonts/FontLCD.h"

static constexpr int BIG_LABEL_PT = 26;


GlobalCtrls::GlobalCtrls(MidiManager& mgr, ER1AudioProcessor& proc)
    : m_SoundPatchManager(mgr.getActiveVoice(), proc.getSoundPresetFolder(), "Sound", "*.er1snd")
    , m_BankPatchManager(&proc, proc.getBankPresetFolder(), "Bank", "*.er1bnk")
    , m_OptionsManager(proc.getOptions())
    , r_MidiManager(mgr)
    , m_Bank("Bank", "Default")
    , m_BankLabel("Bank Label", "BANK:")
    , m_NoteListen(WidgetManager::WidgetID::listen, 0)
    , m_SelectSound(WidgetManager::WidgetID::sound, 0)
    , m_SelectBank(WidgetManager::WidgetID::bank, 0)
    , m_Options(WidgetManager::WidgetID::options, 0)
{
    setInterceptsMouseClicks(false, true);

    m_LCDScreen.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());
    m_SoundPatchManager.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());
    m_BankPatchManager.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());
    m_OptionsManager.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());
    m_Bank.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());
    m_BankLabel.setComponentEffect(dynamic_cast<ER1LAF&>(getLookAndFeel()).getLCDFilter());

    addChildComponent(m_SoundPatchManager);
    addChildComponent(m_BankPatchManager);
    addChildComponent(m_OptionsManager);

    m_Bank.setEditable(false, true);
    m_Bank.onTextChange = [&]() { proc.setPatchName(m_Bank.getText().toStdString()); };

    addAndMakeVisible(m_LCDScreen);
    addAndMakeVisible(m_BankLabel); addAndMakeVisible(m_Bank);
    addAndMakeVisible(m_NoteListen);
    addAndMakeVisible(m_Options);
    addAndMakeVisible(m_SelectBank);
    addAndMakeVisible(m_SelectSound);

    m_SoundPatchManager.addChangeListener(this);
    m_BankPatchManager.addChangeListener(this);

    m_NoteListen.addListener(this);
    m_SelectSound.addListener(this);
    m_SelectBank.addListener(this);
    m_Options.addListener(this);
}

void GlobalCtrls::timerCallback()
{
    if (r_MidiManager.isListening())
        { m_NoteListen.brightness = m_NoteListen.brightness > 0.0f ? 0.0f : 1.0f; }
    else
    {
        stopTimer();
        m_NoteListen.setToggleState(false, juce::dontSendNotification);
        m_NoteListen.brightness = 0.0f;
    }

    m_NoteListen.repaint();
}

void GlobalCtrls::resized()
{
    auto lcdTextColour = getLookAndFeel().findColour(LCDText::ColourIds::textColour).darker(0.1);
    auto& font = FontLCD::defaultFont();

    m_BankLabel.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_BankLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);
    m_Bank.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_Bank.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    auto bounds = getLocalBounds();
    bounds.removeFromTop(46);
    bounds.removeFromLeft(101);
    bounds = bounds.removeFromTop(95);
    bounds = bounds.removeFromLeft(294);

    m_LCDScreen.setBounds(bounds);
    m_SoundPatchManager.setBounds(bounds);
    m_BankPatchManager.setBounds(bounds);
    m_OptionsManager.setBounds(bounds);

    bounds.removeFromTop(2);
    const auto bankBounds = bounds.removeFromTop(BIG_LABEL_PT);

    const auto bankLabelLength = juce::Rectangle<int>(
            bankBounds.getX(), bankBounds.getY(),
            BIG_LABEL_PT + m_BankLabel.getFont().getStringWidthFloat(m_BankLabel.getText()) + 5, bankBounds.getHeight()
    );
    const auto bankLength = juce::Rectangle<int>(
            bankLabelLength.getRight() - BIG_LABEL_PT, bankBounds.getY(),
            bankBounds.getWidth() - (bankBounds.getY() + BIG_LABEL_PT), bankBounds.getHeight()
    );

    m_BankLabel.setBounds(bankLabelLength);
    m_Bank.setBounds(bankLength);

}

void GlobalCtrls::buttonClicked(juce::Button* btn)
{

    if (btn == &m_NoteListen)
    {
        if (r_MidiManager.isListening())
        {
            r_MidiManager.stopListen();
            stopTimer();
            m_NoteListen.brightness = 0.0f;
            m_NoteListen.repaint();
            return;
        }

        r_MidiManager.startListen();
        startTimer(750);
    }

    if (btn == &m_SelectSound)
    {
        if (m_SelectSound.getToggleState())
        {
            m_SelectBank.setToggleState(false, juce::sendNotification);
            m_Options.setToggleState(false, juce::sendNotification);
        }
        m_SoundPatchManager.setVisible(m_SelectSound.getToggleState());
    }


    if (btn == &m_SelectBank)
    {
        if (m_SelectBank.getToggleState())
        {
            m_SelectSound.setToggleState(false, juce::sendNotification);
            m_Options.setToggleState(false, juce::sendNotification);
        }
        m_BankPatchManager.setVisible(m_SelectBank.getToggleState());
    }


    if (btn == &m_Options)
    {
        if (m_Options.getToggleState())
        {
            m_SelectSound.setToggleState(false, juce::sendNotification);
            m_SelectBank.setToggleState(false, juce::sendNotification);
        }

        m_OptionsManager.setVisible(m_Options.getToggleState());
    }

    const auto patchMgrVisible = m_SelectBank.getToggleState() || m_SelectSound.getToggleState() || m_Options.getToggleState();
    m_BankLabel.setVisible(!patchMgrVisible);
    m_Bank.setVisible(!patchMgrVisible);
    m_LCDScreen.setVisible(!patchMgrVisible);
}

void GlobalCtrls::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    sendChangeMessage();
}

void GlobalCtrls::setBankName(const std::string& bank)
{
    m_Bank.setText(bank, juce::dontSendNotification);
    repaint();
}

void GlobalCtrls::setVoice(const ER1SoundPatch::Ptr& patch)
{
    m_LCDScreen.setPatch(patch);
    m_SoundPatchManager.changeTarget(patch);
}
