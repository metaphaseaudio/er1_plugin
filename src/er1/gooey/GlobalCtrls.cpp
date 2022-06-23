//
// Created by Mattb on 6/20/2022.
//

#include "GlobalCtrls.h"
#include "look_and_feel/StandardShapes.h"

GlobalCtrls::GlobalCtrls(MidiManager& mgr)
    : r_MidiManager(mgr)
{
    setInterceptsMouseClicks(false, true);

    addChildComponent(m_PatchManager);

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

    addAndMakeVisible(m_NoteListen); addAndMakeVisible(m_NoteListenLabel);
    addAndMakeVisible(m_Options); addAndMakeVisible(m_LiveModeLabel);
    addAndMakeVisible(m_SelectBank); addAndMakeVisible(m_SelectBankLabel);
    addAndMakeVisible(m_SelectSound); addAndMakeVisible(m_SelectSoundLabel);

    m_NoteListen.addListener(this);
    m_SelectSound.addListener(this);
    m_SelectBank.addListener(this);
    m_Options.addListener(this);
}

void GlobalCtrls::timerCallback()
{
    if (r_MidiManager.isListening())
    {
        m_NoteListen.setState(
            m_NoteListen.getState() == juce::Button::ButtonState::buttonDown
                                    ? juce::Button::ButtonState::buttonNormal
                                    : juce::Button::ButtonState::buttonDown);
    }
    else
    {
        m_NoteListen.setState(juce::Button::ButtonState::buttonNormal);
    }
}

void GlobalCtrls::resized()
{
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
    m_PatchManager.setBounds(bounds.reduced(1));
}

void GlobalCtrls::buttonClicked(juce::Button* btn)
{
    if (btn == &m_NoteListen)
    {
        if (r_MidiManager.isListening())
        {
            r_MidiManager.stopListen();
            stopTimer();
            m_NoteListen.setState(juce::Button::buttonNormal);
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
        m_PatchManager.setVisible(m_SelectSound.getToggleState());
    }


    if (btn == &m_SelectBank)
    {
        if (m_SelectBank.getToggleState())
        {
            m_SelectSound.setToggleState(false, juce::sendNotification);
            m_Options.setToggleState(false, juce::sendNotification);
        }
    }


    if (btn == &m_Options)
    {
        if (m_Options.getToggleState())
        {
            m_SelectSound.setToggleState(false, juce::sendNotification);
            m_SelectBank.setToggleState(false, juce::sendNotification);
        }
    }
}
