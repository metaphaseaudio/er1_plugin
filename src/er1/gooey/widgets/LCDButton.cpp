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
    g.setFont(FontLCD::defaultFont().withPointHeight(12));
    g.drawFittedText(juce::Button::getName(), getLocalBounds(), juce::Justification::centred, 1);
}

LCDToggleButton::LCDToggleButton(const juce::String& name)
    : juce::ToggleButton(name)
{}

void LCDToggleButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    const auto lineWidth = 1;
    const auto toggleColour = getToggleState() ? juce::Colours::red : juce::Colours::red.darker(0.6);

    g.setColour(isMouseOverButton ? toggleColour.brighter() : toggleColour);
    g.drawRect(getLocalBounds(), lineWidth);

    g.setColour(toggleColour);
    g.setFont(FontLCD::defaultFont().withPointHeight(9));
    g.drawFittedText(juce::Button::getName(), getLocalBounds(), juce::Justification::centred, 1);
}
