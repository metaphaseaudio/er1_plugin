//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <JuceHeader.h>
#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"
#include "config_section/ConfigComponent.h"
#include "../widgets/LCDReadout.h"
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundEditorWindow);
};
