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
#include "../../look_and_feel/ER1LAF.h"


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
    KorgKnob m_Pitch;
    KorgKnob m_ModDepth;
    KorgKnob m_ModSpeed;

    KorgComboBox  m_ModType;
    KorgComboBox  m_OscType;
    GlobalOptions& r_Opts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscSectionComponent)
};
