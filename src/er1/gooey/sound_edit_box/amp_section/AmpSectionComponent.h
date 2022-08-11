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
#include "../../../guts/juce_synth/ER1SoundPatch.h"
#include "../../../guts/MidiManager.h"
#include "../../widgets/Header.h"
#include "../../../guts/GlobalOptions.h"


class AmpSectionComponent
    : public juce::Component
    , juce::ChangeListener
{
public:
    explicit AmpSectionComponent(GlobalOptions& opts, AmpParams& params);

    ~AmpSectionComponent() override = default;
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    Header m_Header;
    KorgKnob m_Decay;    juce::Label m_DecayLabel;
    KorgKnob m_Level;    juce::Label m_LevelLabel;
    KorgKnob m_Pan;      juce::Label m_PanLabel;
    KorgKnob m_LowBoost; juce::Label m_LowBoostLabel;
    GlobalOptions& r_Opts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpSectionComponent)
};
