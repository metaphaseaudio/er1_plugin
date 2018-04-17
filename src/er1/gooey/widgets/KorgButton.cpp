//
// Created by mzapp on 4/16/18.
//

#include "KorgButton.h"

KorgButton::KorgButton(const juce::String& name)
    : juce::Button(name)
{}

void KorgButton::paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = getLocalBounds().toFloat().reduced(4);
    g.setColour(isButtonDown ? juce::Colours::pink : juce::Colours::antiquewhite);
    g.fillRoundedRectangle(bounds, 10);
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 10,2);
}
