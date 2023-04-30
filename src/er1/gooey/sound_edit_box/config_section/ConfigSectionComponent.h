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
    explicit ConfigSectionComponent(ER1SoundPatch& params);
    void resized() override;

private:
    LCDScreen m_Screen;
};
