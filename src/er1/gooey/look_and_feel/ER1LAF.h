//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"

class ER1LAF
    : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider
    (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
     const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawKorgButton
    (juce::Graphics& g, KorgButton& button, bool isMouseOverButton, bool isButtonDown);

    void drawKorgToggleButton
        (juce::Graphics& g, KorgToggleButton& button, bool isMouseOverButton, bool isButtonDown);
};
