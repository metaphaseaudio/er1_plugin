/*
  ==============================================================================

    OscSectionComponent.h
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../widgets/KorgButton.h"
#include "WaveSelectors.h"

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
    OscSectionComponent();
    ~OscSectionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
private:
    juce::Slider m_Pitch;    juce::Label m_PitchLabel;
    juce::Slider m_ModDepth; juce::Label m_ModDepthLabel;
    juce::Slider m_ModSpeed; juce::Label m_ModSpeedLabel;

    juce::ComboBox  m_ModType;  juce::Label m_ModTypeLabel;
    juce::ComboBox  m_OscType;  juce::Label m_OscTypeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
