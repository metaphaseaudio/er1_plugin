/*
  ==============================================================================

    AmpSectionComponent.h
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <er1_dsp/Voice.h>
#include "../../widgets/KorgKnob.h"


class AmpSectionComponent
    : public juce::Component
{
public:
    AmpSectionComponent(const AmpParameters& params);
    ~AmpSectionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setVoice(meta::ER1::Voice* voice);

private:
    KorgKnob m_Decay;    juce::Label m_DecayLabel;
    KorgKnob m_Level;    juce::Label m_LevelLabel;
    KorgKnob m_Pan;      juce::Label m_PanLabel;
    KorgKnob m_LowBoost; juce::Label m_LowBoostLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSectionComponent)
};
