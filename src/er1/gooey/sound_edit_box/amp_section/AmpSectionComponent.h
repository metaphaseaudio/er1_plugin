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
    ~AmpSectionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider m_Decay;    juce::Label m_DecayLabel;
    juce::Slider m_Level;    juce::Label m_LevelLabel;
    juce::Slider m_Pan;      juce::Label m_PanLabel;
    juce::Slider m_LowBoost; juce::Label m_LowBoostLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSectionComponent)
};
