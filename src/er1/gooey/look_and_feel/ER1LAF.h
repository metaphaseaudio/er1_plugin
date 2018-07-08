//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>

class ER1LAF
    : public juce::LookAndFeel_V4
{
    void drawRotarySlider
    (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
     const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;
};
