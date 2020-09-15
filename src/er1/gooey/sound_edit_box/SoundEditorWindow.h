//
// Created by mzapp on 7/8/18.
//

#pragma once

#include <JuceHeader.h>
#include "osc_section/OscSectionComponent.h"
#include "amp_section/AmpSectionComponent.h"
#include <meta/gooey/RadioGrid.h>

class SoundEditorWindow
    : public juce::Component
    , juce::ChangeListener
{
public:
    SoundEditorWindow();

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    OscSectionComponent m_OscSection;
    AmpSectionComponent m_AmpSection;
    meta::RadioGrid<KorgToggleButton, 4, 4> m_PadGrid;
};
