/*
  ==============================================================================

    Transport.h
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Transport
    : public juce::Component
{
public:
    Transport();
    ~Transport();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Transport)
};
