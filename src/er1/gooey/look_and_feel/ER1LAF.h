//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"
#include "../widgets/KorgPad.h"
#include "../widgets/SelectorButton.h"


class ER1LAF
    : public juce::LookAndFeel_V4
{
public:
    ER1LAF();

    void drawRotarySlider
    (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
     const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawKorgPad(juce::Graphics& g, juce::Component& pad, bool isPadLit, bool isPadDown);

    void drawKorgButton
    (juce::Graphics& g, KorgButton& button, bool isMouseOverButton, bool isButtonDown);

    void drawKorgToggleButton
        (juce::Graphics& g, KorgToggleButton& button, bool isMouseOverButton, bool isButtonDown);
private:
    void drawPad(juce::Graphics& g, const juce::Component& area, const juce::Colour& internalColour);
};
