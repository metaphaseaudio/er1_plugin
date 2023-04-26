/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "../gooey/widgets/DividerLine.h"
#include "../guts/ER1AudioProcessor.h"
#include "../gooey/sound_edit_box/SoundEditorWindow.h"
#include "../gooey/voice_selector/VoiceSelector.h"
#include "look_and_feel/ER1LAF.h"
#include "GlobalCtrls.h"

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

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    ER1LAF m_LAF;
    ER1AudioProcessor& processor;
    std::vector<std::unique_ptr<SoundEditorWindow>>  m_SoundEditorWindows;
    DividerLine m_Divider;
    std::unique_ptr<VoiceSelector> p_VoiceSelector;
    std::unique_ptr<GlobalCtrls> p_GlobalCtrls;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessorEditor);
};
