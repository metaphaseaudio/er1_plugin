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
#include "../gooey/left_box/Transport.h"
#include "left_box/RedBox.h"
#include "../gooey/sound_edit_box/SoundEditorWindow.h"
#include "../gooey/grid/SequenceGrid.h"
#include "../gooey/grid/PadGrid.h"
#include "../gooey/grid/SoundGrid.h"

//==============================================================================
/**
*/
class ER1AudioProcessorEditor
    : public juce::AudioProcessorEditor
    , juce::ChangeListener
{
public:
    explicit ER1AudioProcessorEditor(ER1AudioProcessor&);
    ~ER1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    enum { SEQUENCE, PADS, SOUNDS };

    ER1AudioProcessor& processor;
    juce::TabbedComponent m_Tabs;
    SoundEditorWindow m_SoundEditorWindow;
    SequenceGrid m_Sequence;
    PadGrid m_Pads;
    SoundGrid m_Sounds;
    meta::RadioButtonSet<KorgToggleButton, 4> m_Bank;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessorEditor)
};
