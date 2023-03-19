//
// Created by Mattb on 6/20/2022.
//

#include "GlobalCtrls.h"
#include "look_and_feel/StandardShapes.h"
#include "fonts/FontLCD.h"

#define BIG_LABEL_PT 19


GlobalCtrls::GlobalCtrls(MidiManager& mgr, ER1AudioProcessor& proc)
    : m_SoundPatchManager(mgr.getActiveVoice(), proc.getSoundPresetFolder(), "Sound", "*.er1snd")
    , m_BankPatchManager(&proc, proc.getBankPresetFolder(), "Bank", "*.er1bnk")
    , m_OptionsManager(proc.getOptions())
    , r_MidiManager(mgr)
    , m_Bank("Bank", "Default")
    , m_BankLabel("Bank Label", "BNK:")
{
    setInterceptsMouseClicks(false, true);

    m_SoundPatchManager.setLookAndFeel(&m_LCDLAF);
    m_BankPatchManager.setLookAndFeel(&m_LCDLAF);
    m_OptionsManager.setLookAndFeel(&m_LCDLAF);

    addChildComponent(m_SoundPatchManager);
    addChildComponent(m_BankPatchManager);
    addChildComponent(m_OptionsManager);

    m_NoteListenLabel.setText("LISTEN", juce::dontSendNotification);
    m_LiveModeLabel.setText("OPTIONS", juce::dontSendNotification);
    m_SelectBankLabel.setText("BANK", juce::dontSendNotification);
    m_SelectSoundLabel.setText("SOUND", juce::dontSendNotification);

    m_NoteListenLabel.setJustificationType(juce::Justification::centred);
    m_LiveModeLabel.setJustificationType(juce::Justification::centred);
    m_SelectBankLabel.setJustificationType(juce::Justification::centred);
    m_SelectSoundLabel.setJustificationType(juce::Justification::centred);

    m_NoteListenLabel.setFont(m_NoteListenLabel.getFont().withPointHeight(8));
    m_LiveModeLabel.setFont(m_LiveModeLabel.getFont().withPointHeight(8));
    m_SelectBankLabel.setFont(m_SelectBankLabel.getFont().withPointHeight(8));
    m_SelectSoundLabel.setFont(m_SelectSoundLabel.getFont().withPointHeight(8));

    m_NoteListenLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    m_LiveModeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    m_SelectBankLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    m_SelectSoundLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);

    m_Bank.setEditable(false, true);
    m_Bank.onTextChange = [&]() { proc.setPatchName(m_Bank.getText().toStdString()); };

    addAndMakeVisible(m_BankLabel); addAndMakeVisible(m_Bank);
    addAndMakeVisible(m_NoteListen); addAndMakeVisible(m_NoteListenLabel);
    addAndMakeVisible(m_Options); addAndMakeVisible(m_LiveModeLabel);
    addAndMakeVisible(m_SelectBank); addAndMakeVisible(m_SelectBankLabel);
    addAndMakeVisible(m_SelectSound); addAndMakeVisible(m_SelectSoundLabel);

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
    auto button = StandardShapes::smallSquareButton;
    auto buttonRow = bounds.removeFromBottom(button.getHeight() - 5);
    auto labelRow = bounds.removeFromBottom(20);
    labelRow = labelRow.withY(labelRow.getY() + 9);
    labelRow.removeFromLeft(5);
    labelRow.removeFromRight(5);
    buttonRow.removeFromLeft(5);
    buttonRow.removeFromRight(5);

    const auto btnWidth = buttonRow.getWidth() / 4;

    m_NoteListen.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2)); m_NoteListenLabel.setBounds(labelRow.removeFromLeft(btnWidth));
    m_SelectSound.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2)); m_SelectSoundLabel.setBounds(labelRow.removeFromLeft(btnWidth));
    m_SelectBank.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2)); m_SelectBankLabel.setBounds(labelRow.removeFromLeft(btnWidth));
    m_Options.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2)); m_LiveModeLabel.setBounds(labelRow.removeFromLeft(btnWidth));

    bounds = getLocalBounds().reduced(5);
    bounds.removeFromBottom(button.getHeight());
    bounds = bounds.reduced(2);

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
