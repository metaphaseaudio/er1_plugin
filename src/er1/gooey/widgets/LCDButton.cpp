//
// Created by Mattb on 6/25/2022.
//

#include "LCDButton.h"
#include "../fonts/FontLCD.h"

LCDButton::LCDButton(const juce::String& name)
    : juce::Button(name)
{}

void LCDButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    const auto lineWidth = 1;
    g.setColour(isMouseOverButton ? juce::Colours::red : juce::Colours::red.darker());
    g.drawRect(getLocalBounds(), lineWidth);

    g.setColour(isButtonDown ? juce::Colours::red.darker() : juce::Colours::red);
    g.setFont(FontLCD::defaultFont());
    g.drawFittedText(juce::Button::getName(), getLocalBounds().reduced(2), juce::Justification::centred, 1);
}

