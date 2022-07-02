//
// Created by Matt on 9/17/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/LCDText.h"
#include "../../widgets/LCDButton.h"
#include "../../../guts/juce_synth/SoundParameterBlocks.h"

class LCDScreen
    : public juce::Component
{
public:
    explicit LCDScreen(ConfigParams& config);

    void paint (juce::Graphics&) override;
    void resized() override;
    void refreshText(juce::NotificationType notifiy);
private:
    ConfigParams& r_Config;
    LCDText m_Name, m_MidiNote, m_MidiChan, m_AudioBus;
    LCDToggleButton m_NoteFollow, m_Solo, m_Mute;
    juce::Label m_NameLabel, m_MidiNoteLabel, m_MidiChanLabel, m_AudioBusLabel;
};
