//
// Created by Mattb on 6/20/2022.
//

#include "GlobalCtrls.h"
#include "look_and_feel/StandardShapes.h"

GlobalCtrls::GlobalCtrls(MidiManager& mgr)
    : r_MidiManager(mgr)
{
    addAndMakeVisible(m_NoteListen);
    addAndMakeVisible(m_LiveMode);

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
    auto bounds = getLocalBounds().reduced(5);
    auto button = StandardShapes::smallSquareButton;
    auto buttonRow = bounds.removeFromBottom(button.getHeight());
    m_NoteListen.setBounds(button.withX(buttonRow.getTopLeft().x).withY(buttonRow.getTopLeft().y));
    m_LiveMode.setBounds(button.withX(buttonRow.getTopRight().x - button.getWidth()).withY(buttonRow.getTopLeft().y));
}

void GlobalCtrls::buttonClicked(juce::Button* btn)
{
    if (btn == &m_NoteListen)
    {
        if (r_MidiManager.isListening())
        {
            r_MidiManager.stopListen();
            return;
        }

        r_MidiManager.startListen();
        startTimer(1000);
    }
}
