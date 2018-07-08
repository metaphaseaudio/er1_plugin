/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../gooey/widgets/DividerLine.h"
#include "../guts/ER1AudioProcessor.h"
#include "../gooey/grid/Grid.h"
#include "../gooey/left_box/Transport.h"
#include "left_box/RedBox.h"
#include "../gooey/sound_edit_box/SoundEditorWindow.h"
#include "../gooey/grid/GridBankSelector.h"

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
    juce::TabbedButtonBar m_Tabs;
    SoundEditorWindow m_SoundEditorWindow;
    Grid m_Grid;
    GridBankSelector m_Bank;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessorEditor)
};
