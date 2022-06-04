/*
  ==============================================================================

    OscSectionComponent.h
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/KorgButton.h"
#include "../../widgets/KorgKnob.h"
#include "../../widgets/KorgComboBox.h"
#include "../../../guts/juce_synth/ER1ControlBlock.h"


class OscSectionComponent
    : public juce::Component
{
public:
    explicit OscSectionComponent(OscParams& params);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    KorgKnob m_Pitch;    juce::Label m_PitchLabel;
    KorgKnob m_ModDepth; juce::Label m_ModDepthLabel;
    KorgKnob m_ModSpeed; juce::Label m_ModSpeedLabel;

    KorgComboBox  m_ModType;  juce::Label m_ModTypeLabel;
    KorgComboBox  m_OscType;  juce::Label m_OscTypeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
