//
// Created by Mattb on 6/25/2022.
//

#include "LCDButton.h"
#include "../fonts/FontLCD.h"
#include "LCDText.h"

LCDButton::LCDButton(const juce::String& name)
    : juce::Button(name)
{}

void LCDButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    const auto colour = getLookAndFeel().findColour(LCDText::ColourIds::textColour);
    const auto lineWidth = 1;
    const auto localBounds = getLocalBounds();

    g.setColour(isMouseOverButton ? colour.brighter(0.5f) : colour);
    g.drawRect(localBounds, lineWidth);

    g.setColour(isButtonDown ? colour.withAlpha(0.75f) : colour);
    g.setFont(FontLCD::defaultFont().withPointHeight(localBounds.getHeight() * 0.8f));
    g.drawFittedText(juce::Button::getName(), getLocalBounds(), juce::Justification::centred, 1);
}

LCDToggleButton::LCDToggleButton(const juce::String& name)
    : juce::ToggleButton(name)
{}

void LCDToggleButton::paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    const auto colour = getLookAndFeel().findColour(LCDText::ColourIds::textColour);
    const auto lineWidth = 1;
    const auto localBounds = getLocalBounds();
    const auto toggleColour = getToggleState() ? colour.withAlpha(0.75f) : colour;

    g.setColour(isMouseOverButton ? toggleColour.brighter(0.5f) : toggleColour);
    g.drawRect(getLocalBounds(), lineWidth);

    g.setColour(toggleColour);
    g.setFont(FontLCD::defaultFont().withPointHeight(localBounds.getHeight() * 0.8f));
    g.drawFittedText(juce::Button::getName(), getLocalBounds(), juce::Justification::centred, 1);
}
