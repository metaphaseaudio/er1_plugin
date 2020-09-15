//
// Created by Matt on 9/13/2020.
//

#include "KorgPad.h"
#include "../look_and_feel/ER1LAF.h"


juce::MidiMessage KorgPad::getMidiMessageForMouseEvent(const juce::MouseEvent& e, bool down)
{
    return down ? juce::MidiMessage::noteOn(chan, note, 1.0f) : juce::MidiMessage::noteOff(chan, note);
}

void KorgPad::handleMessage(const juce::MidiMessage& msg)
{
    if (!msg.isNoteOnOrOff()
        || msg.getNoteNumber() != note
        || msg.getChannel() != chan)
    { return; }

    m_padIsLit = msg.isNoteOn();
    repaint();
}

void KorgPad::paint(juce::Graphics& g)
{
    static_cast<ER1LAF&>(getLookAndFeel()).drawKorgPad
            (g, *this, m_padIsLit, isMouseButtonDown());
}

KorgPad::KorgPad(meta::MidiState& state)
    : MidiComponent(state)
    , m_padIsLit(false)
    , note(0)
    , chan(0)
{}
