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
#include "../../../guts/juce_synth/ER1SoundPatch.h"
#include "../../../guts/MidiManager.h"
#include "../../widgets/Header.h"
#include "../../../guts/GlobalOptions.h"


class OscSectionComponent
    : public juce::Component
    , juce::ChangeListener
{
public:
    explicit OscSectionComponent(GlobalOptions& opts, OscParams& params);
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    Header m_Header;
    KorgKnob m_Pitch;    juce::Label m_PitchLabel;
    KorgKnob m_ModDepth; juce::Label m_ModDepthLabel;
    KorgKnob m_ModSpeed; juce::Label m_ModSpeedLabel;

    KorgComboBox  m_ModType;  juce::Label m_ModTypeLabel;
    KorgComboBox  m_OscType;  juce::Label m_OscTypeLabel;
    GlobalOptions& r_Opts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
