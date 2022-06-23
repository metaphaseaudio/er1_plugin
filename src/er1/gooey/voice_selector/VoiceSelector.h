//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/LCDText.h"
#include "../widgets/KorgButton.h"
#include "../../guts/juce_synth/ER1ControlBlock.h"
#include "../../guts/MidiManager.h"


class VoiceSelector
    : public juce::Component
    , public juce::ChangeBroadcaster
{
public:
    VoiceSelector(MidiManager& midiManager, juce::ReferenceCountedArray<ER1ControlBlock>& sounds);

    void resized() override;
    void paint(juce::Graphics& g) override;

    int getSelected() const;

private:
    int selected = 0;
    std::vector<std::unique_ptr<KorgToggleButton>> m_Buttons;
    std::vector<std::unique_ptr<KorgBooleanParameterButton>> m_RingButtons;
    std::vector<std::unique_ptr<juce::Component>> m_Arrows;
};


