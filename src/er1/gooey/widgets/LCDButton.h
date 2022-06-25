//
// Created by Mattb on 6/25/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LCDButton
    : public juce::Button
{
public:
    explicit LCDButton(const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
};
