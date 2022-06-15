//
// Created by Mattb on 6/9/2022.
//

#pragma once
#include "LCDScreen.h"
#include "../../../guts/MidiManager.h"
#include "../../widgets/KorgButton.h"


class ConfigSectionComponent
    : public juce::Component
{
public:
    ConfigSectionComponent(MidiManager& midiManager, ConfigParams& params);
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    LCDScreen m_Screen;
    KorgButton m_LiveMode, m_NoteListen;
};
