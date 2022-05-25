//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/gooey/RadioButton.h>
#include "../widgets/LCDText.h"
#include "../widgets/KorgButton.h"
#include "../../guts/juce_synth/ER1Sound.h"

class PatchSelector
    : public juce::Component
    , public juce::ChangeBroadcaster
{
public:
    PatchSelector();

    void resized() override;
    void paint(juce::Graphics& g) override;

    int getSelected() const;

private:
    int selected = 0;
    std::array<KorgToggleButton, 16> m_Buttons;
    std::array<KorgToggleButton, 5> m_RingButtons;
};


