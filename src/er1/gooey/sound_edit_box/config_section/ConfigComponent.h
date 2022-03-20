//
// Created by Matt on 9/17/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../../widgets/LCDText.h"
#include "../../../guts/juce_synth/SoundParameterBlocks.h"

class ConfigComponent
    : public juce::Component
    , juce::TextEditor::Listener
{
public:
    ConfigComponent(ConfigParams& config);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    /** Called when the user presses the return key. */
    void textEditorReturnKeyPressed(juce::TextEditor&) override;

    /** Called when the text editor loses focus. */
    void textEditorFocusLost(juce::TextEditor&) override;

    ConfigParams& r_Config;
    LCDText m_Name, m_MidiNoteLabel, m_MidiChanLabel;
    juce::TextEditor m_MidiNote, m_MidiChan;
};


