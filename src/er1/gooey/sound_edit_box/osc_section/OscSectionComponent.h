/*
  ==============================================================================

    OscSectionComponent.h
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveSelectors.h"
#include "../../widgets/KorgButton.h"
#include "../../widgets/KorgKnob.h"
#include "../../../guts/juce_synth/ER1Sound.h"
#include <er1_dsp/Voice.h>


class OscSectionComponent
    : public juce::Component
    , juce::ComboBox::Listener
{
public:
    enum WaveformType {
        SINE = 1,
        TRI,
        SQUARE,
        STEP,
        NOISE,
        SWEEP
    };


    explicit OscSectionComponent(OscParams& params);

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;

private:
    KorgKnob m_Pitch;    juce::Label m_PitchLabel;
    KorgKnob m_ModDepth; juce::Label m_ModDepthLabel;
    KorgKnob m_ModSpeed; juce::Label m_ModSpeedLabel;

    juce::ComboBox  m_ModType;  juce::Label m_ModTypeLabel;
    juce::ComboBox  m_OscType;  juce::Label m_OscTypeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
