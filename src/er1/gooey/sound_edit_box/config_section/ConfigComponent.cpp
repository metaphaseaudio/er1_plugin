//
// Created by Matt on 9/17/2020.
//

#include "ConfigComponent.h"
#include "../../look_and_feel/ER1Colours.h"

#define LABEL_HEIGHT 22


ConfigComponent::ConfigComponent()
    : m_MidiNote("Midi note"), m_MidiNoteLabel("Midi note label", "Midi note:")
{
    m_MidiNote.setInputRestrictions(3, "0123456789");
    m_MidiNote.addListener(this);
    m_MidiNote.setText("1", false);

    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
}

void ConfigComponent::paint(juce::Graphics& g)
{
    auto header = getLocalBounds().removeFromTop(LABEL_HEIGHT);

    g.setColour(juce::Colours::black);
    g.fillRect(header);
    g.setFont(g.getCurrentFont().boldened());
    g.setColour(ER1Colours::defaultForeground);
    g.drawFittedText("VOICE SETUP", header, juce::Justification::centred, 1);
}

void ConfigComponent::resized()
{
    auto bounds = getLocalBounds();

    // Ditch the header
    bounds.removeFromTop(LABEL_HEIGHT); bounds.removeFromTop(5);

    auto row = bounds.removeFromTop(LABEL_HEIGHT);

    m_MidiNoteLabel.setBounds(row.removeFromLeft(m_MidiNoteLabel.getFont().getStringWidth(m_MidiNoteLabel.getText())));
    row.removeFromLeft(5);
    m_MidiNote.setBounds(row);
}

void ConfigComponent::textEditorReturnKeyPressed(juce::TextEditor&)
{}

void ConfigComponent::textEditorFocusLost(juce::TextEditor&)
{}
