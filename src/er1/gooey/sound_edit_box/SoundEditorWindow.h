//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"
#include "delay_section/DelaySectionComponent.h"
#include "config_section/ConfigComponent.h"
#include "../widgets/LCDText.h"
#include "../../guts/ER1AudioProcessor.h"
#include "../../guts/juce_synth/ER1Sound.h"
#include <meta/gooey/RadioGrid.h>
#include <er1_dsp/Voice.h>


class SoundEditorWindow
    : public juce::Component
    , juce::ChangeListener
{
public:
    explicit SoundEditorWindow(ER1Sound::Ptr sound);
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    ConfigComponent m_VoiceSetup;
    OscSectionComponent m_OscSection;
    AmpSectionComponent m_AmpSection;
    DelaySectionComponent m_DelaySection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundEditorWindow);
};
