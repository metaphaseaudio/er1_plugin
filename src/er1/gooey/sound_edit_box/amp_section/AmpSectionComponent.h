/*
  ==============================================================================

    AmpSectionComponent.h
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/KorgKnob.h"
#include "../../../guts/juce_synth/ER1ControlBlock.h"


class AmpSectionComponent
    : public juce::Component
{
public:
    explicit AmpSectionComponent(AmpParams& params);
    ~AmpSectionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    KorgKnob m_Decay;    juce::Label m_DecayLabel;
    KorgKnob m_Level;    juce::Label m_LevelLabel;
    KorgKnob m_Pan;      juce::Label m_PanLabel;
    KorgKnob m_LowBoost; juce::Label m_LowBoostLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSectionComponent)
};
