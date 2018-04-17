//
// Created by mzapp on 4/16/18.
//
#pragma once

#include <JuceHeader.h>

class KorgButton
    : public juce::Button
{
public:
    KorgButton(const juce::String& name);
    virtual void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
};
