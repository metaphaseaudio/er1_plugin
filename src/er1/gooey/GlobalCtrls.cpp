//
// Created by Mattb on 6/20/2022.
//

#include "GlobalCtrls.h"
#include "look_and_feel/StandardShapes.h"

GlobalCtrls::GlobalCtrls(MidiManager& mgr)
    : r_MidiManager(mgr)
{
    setInterceptsMouseClicks(false, true);
    addAndMakeVisible(m_NoteListen);
    addAndMakeVisible(m_LiveMode);
    addAndMakeVisible(m_SelectBank);
    addAndMakeVisible(m_SelectSound);

    m_NoteListen.addListener(this);
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
    buttonRow.removeFromLeft(5);
    buttonRow.removeFromRight(5);

    const auto btnWidth = buttonRow.getWidth() / 4;

    m_NoteListen.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2));
    m_SelectSound.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2));
    m_SelectBank.setBounds(buttonRow.removeFromLeft(btnWidth).reduced(2));
    m_LiveMode.setBounds(buttonRow.reduced(2));
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
}
