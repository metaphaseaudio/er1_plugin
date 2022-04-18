//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/gooey/RadioButton.h>
#include "../widgets/LCDText.h"
#include "../widgets/KorgButton.h"


class PatchSelector
    : public juce::Component
    , juce::Button::Listener
{
public:
    PatchSelector();
    void resized() override;
    void paint(juce::Graphics& g) override;


private:
    void buttonClicked(juce::Button* btn) override;

    std::array<KorgToggleButton, 16> m_Buttons;
    std::array<KorgToggleButton, 8> m_RingButtons;
};


