//
// Created by Matt on 9/19/2020.
//

#include "PatchSelector.h"
#include "../look_and_feel/ER1Colours.h"


PatchSelector::PatchSelector()
    : m_LCDLabel("LCD Label", "Patch Num:")
    , m_LockMidiLabel("Lock Midi Label", "Change on midi")
{
//    m_LCD.setText("ER-1");
//    addAndMakeVisible(m_LCD);
    addAndMakeVisible(m_LCDLabel);
    addAndMakeVisible(m_LockMidi);
    addAndMakeVisible(m_LockMidiLabel);
    m_LockMidi.addListener(this);
}

void PatchSelector::resized()
{
    auto bounds = getLocalBounds();
    auto lcdLabal = bounds.removeFromTop(45);
    m_LCDLabel.setBounds(lcdLabal.removeFromLeft(45));
//    m_LCD.setBounds(lcdLabal.reduced(5));
    auto lockMidi = bounds.removeFromTop(30);
    m_LockMidi.setBounds(lockMidi.removeFromLeft(30).reduced(3));
    m_LockMidiLabel.setBounds(lockMidi);
}

void PatchSelector::paint(juce::Graphics& g)
{
    g.setColour(ER1Colours::korgRed);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 5.0f);
}

bool PatchSelector::shouldChangeOnMidi() const { return m_LockMidi.getToggleState(); }

void PatchSelector::buttonClicked(juce::Button* btn)
{

}
