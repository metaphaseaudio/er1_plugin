/*
  ==============================================================================

    AmpSectionComponent.h
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AmpSectionComponent
    : public juce::Component
{
public:
    AmpSectionComponent();
    ~AmpSectionComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider m_Decay;
    juce::Slider m_Level;
    juce::Slider m_Pan;
    juce::Slider m_LowBoost;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSectionComponent)
};
