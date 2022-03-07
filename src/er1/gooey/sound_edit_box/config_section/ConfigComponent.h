//
// Created by Matt on 9/17/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class ConfigComponent
    : public juce::Component
    , juce::TextEditor::Listener
{
public:
    ConfigComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    /** Called when the user presses the return key. */
    void textEditorReturnKeyPressed(juce::TextEditor&) override;

    /** Called when the text editor loses focus. */
    void textEditorFocusLost(juce::TextEditor&) override;

    juce::Label m_MidiNoteLabel;
    juce::TextEditor m_MidiNote;
};


