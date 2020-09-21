//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <JuceHeader.h>
#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"
#include "config_section/ConfigComponent.h"
#include "../widgets/LCDReadout.h"
#include "patch_selector/PatchSelector.h"
#include <meta/gooey/RadioGrid.h>
#include <er1_dsp/Voice.h>


class SoundEditorWindow
    : public juce::Component
    , juce::ChangeListener
{
public:
    SoundEditorWindow();

    void setVoice(meta::ER1::Voice* voice);

    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    ConfigComponent m_VoiceSetup;
    OscSectionComponent m_OscSection;
    AmpSectionComponent m_AmpSection;
    PatchSelector m_PatchSelector;
    meta::RadioGrid<KorgToggleButton, 4, 4, 2> m_PadGrid;
};
