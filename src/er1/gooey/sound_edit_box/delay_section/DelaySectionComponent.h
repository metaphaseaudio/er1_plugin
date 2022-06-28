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
#include "../../widgets/KorgButton.h"
#include "../../../guts/juce_synth/ER1ControlBlock.h"
#include "../../../guts/MidiManager.h"
#include "../../widgets/Header.h"


class DelaySectionComponent
    : public juce::Component
{
public:
    explicit DelaySectionComponent(DelayParams& params);
    ~DelaySectionComponent() override = default;
    void resized() override;

private:
    Header m_Header;
    KorgKnob m_Time;  juce::Label m_TimeLabel;
    KorgKnob m_Depth; juce::Label m_DepthLabel;
    KorgBooleanParameterButton m_Sync; juce::Label m_SyncLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelaySectionComponent)
};
