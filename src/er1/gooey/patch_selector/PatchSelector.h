//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/LCDReadout.h"
#include "../widgets/KorgButton.h"


class PatchSelector
    : public juce::Component
    , juce::Button::Listener
{
public:
    PatchSelector();
    void resized() override;
    void paint(juce::Graphics& g) override;

    bool shouldChangeOnMidi() const;

private:
    void buttonClicked(juce::Button* btn) override;
    LCDReadout m_LCD;
    juce::Label m_LCDLabel, m_LockMidiLabel;
    KorgToggleButton m_LockMidi;
};


