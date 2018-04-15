/*
  ==============================================================================

    RedBox.h
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RedBox
    : public juce::Component
{
public:
    RedBox();
    ~RedBox();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedBox)
};
