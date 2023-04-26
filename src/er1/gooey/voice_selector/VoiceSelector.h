//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/LCDText.h"
#include "../widgets/KorgButton.h"
#include "../../guts/juce_synth/ER1SoundPatch.h"
#include "../../guts/MidiManager.h"
#include "../widgets/Header.h"
#include "../../guts/juce_synth/ER1Voice.h"


class VoiceSelector
    : public juce::Component
    , public juce::ChangeBroadcaster
    , public juce::Timer
{
public:
    VoiceSelector(MidiManager& midiManager, const std::vector<std::unique_ptr<ER1Voice>>& voices);
    int getSelected() const;

private:
    void timerCallback() override;

    const std::vector<std::unique_ptr<ER1Voice>>& r_Voices;
    std::vector<std::unique_ptr<KorgToggleButton>> m_Buttons;
    std::vector<std::unique_ptr<KorgBooleanParameterButton>> m_RingButtons;
};


