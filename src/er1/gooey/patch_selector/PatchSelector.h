//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/LCDText.h"
#include "../widgets/KorgButton.h"
#include "../../guts/juce_synth/ER1ControlBlock.h"

class PatchSelector
    : public juce::Component
    , public juce::ChangeBroadcaster
{
public:
    explicit PatchSelector(juce::ReferenceCountedArray<ER1ControlBlock>& sounds);

    void resized() override;
    void paint(juce::Graphics& g) override;

    int getSelected() const;

private:
    int selected = 0;
    std::array<KorgToggleButton, 16> m_Buttons;
    std::vector<std::unique_ptr<KorgBooleanParameterButton>> m_RingButtons;
};


