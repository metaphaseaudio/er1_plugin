//
// Created by Matt on 9/17/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/LCDText.h"
#include "../../../guts/juce_synth/SoundParameterBlocks.h"

class LCDScreen
    : public juce::Component
{
public:
    explicit LCDScreen(ConfigParams& config);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ConfigParams& r_Config;
    juce::Label m_Name, m_MidiNote, m_MidiChan, m_AudioBus;
    juce::Label /*m_NameLabel,*/ m_MidiNoteLabel, m_MidiChanLabel, m_AudioBusLabel;
};


