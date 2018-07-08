//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <JuceHeader.h>
#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"

class SoundEditorWindow
    : public juce::Component
{
public:
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    OscSectionComponent m_OscSection;
    AmpSectionComponent m_AmpSection;
};
