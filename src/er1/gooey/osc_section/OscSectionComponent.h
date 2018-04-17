/*
  ==============================================================================

    OscSectionComponent.h
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"

class OscSectionComponent
    : public juce::Component
{
public:
    OscSectionComponent();
    ~OscSectionComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider m_Pitch;
    juce::Slider m_ModDepth;
    juce::Slider m_ModSpeed;
    juce::Slider m_ModType;
    KorgButton m_OscType;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
