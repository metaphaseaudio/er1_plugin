//
// Created by Matt on 9/17/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/LCDText.h"
#include "../../../guts/juce_synth/SoundParameterBlocks.h"

class ConfigComponent
    : public juce::Component
{
public:
    ConfigComponent(ConfigParams& config);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ConfigParams& r_Config;
    LCDText m_Name, m_MidiNote, m_MidiChan;
    LCDText /*m_NameLabel,*/ m_MidiNoteLabel, m_MidiChanLabel;
};


