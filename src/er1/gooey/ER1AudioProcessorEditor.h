/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <meta/gooey/RadioButton.h>
#include "../gooey/widgets/DividerLine.h"
#include "../guts/ER1AudioProcessor.h"
#include "meta/gooey/ButtonGrid.h"
#include "../gooey/sound_edit_box/SoundEditorWindow.h"
#include "../gooey/grid/SequenceGrid.h"
#include "../gooey/grid/PadGrid.h"
#include "../gooey/grid/SoundGrid.h"
#include "look_and_feel/ER1LAF.h"

//==============================================================================
/**
*/
class ER1AudioProcessorEditor
    : public juce::AudioProcessorEditor
{
public:
    explicit ER1AudioProcessorEditor(ER1AudioProcessor&);
    ~ER1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    ER1LAF m_LAF;
    ER1AudioProcessor& processor;
    SoundEditorWindow m_SoundEditorWindow;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessorEditor);
};
