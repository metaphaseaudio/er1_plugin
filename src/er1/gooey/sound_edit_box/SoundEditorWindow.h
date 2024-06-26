//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"
#include "delay_section/DelaySectionComponent.h"

#include "../widgets/LCDText.h"
#include "../widgets/DividerLine.h"
#include "../../guts/ER1AudioProcessor.h"
#include "../../guts/juce_synth/ER1SoundPatch.h"


class SoundEditorWindow
    : public juce::Component
    , public juce::ChangeListener
{
public:
    explicit SoundEditorWindow(GlobalOptions& opts, const ER1SoundPatch::Ptr& sound);
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* broadcaster) override;
    OscSectionComponent m_OscSection;
    AmpSectionComponent m_AmpSection;
    DelaySectionComponent m_DelaySection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundEditorWindow);
};
