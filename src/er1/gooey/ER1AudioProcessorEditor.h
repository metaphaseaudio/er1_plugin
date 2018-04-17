/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../gooey/widgets/DividerLine.h"
#include "../gooey/osc_section/OscSectionComponent.h"
#include "../guts/ER1AudioProcessor.h"
#include "../gooey/sequencer/Sequencer.h"
#include "../gooey/left_box/Transport.h"
#include "left_box/RedBox.h"
#include "amp_section/AmpSectionComponent.h"

//==============================================================================
/**
*/
class ER1AudioProcessorEditor
    : public juce::AudioProcessorEditor
{
public:
    ER1AudioProcessorEditor (ER1AudioProcessor&);
    ~ER1AudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ER1AudioProcessor& processor;
    RedBox m_RedBoxComponent;
    AmpSectionComponent m_AmpSectionComponent;
    DividerLine m_AmpOscDiv;
    OscSectionComponent m_OscSectionComponent;
    Transport m_TransportComponent;
    Sequencer m_Sequencer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessorEditor)
};
