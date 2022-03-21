//
// Created by Matt on 9/17/2020.
//

#include "ConfigComponent.h"
#include "../../look_and_feel/ER1Colours.h"

#define LABEL_HEIGHT 22


ConfigComponent::ConfigComponent(ConfigParams& config)
    : r_Config(config)
    , m_Name("Sound name", "", 9)
    , m_MidiNote("Midi note"), m_MidiNoteLabel("Midi note label", "note:", 5)
    , m_MidiChan("Midi chan"), m_MidiChanLabel("Midi chan label", "chan:", 5)
{
    m_MidiNote.setInputRestrictions(3, "0123456789");
    m_MidiChan.setInputRestrictions(3, "0123456789");
    m_MidiNote.addListener(this); m_MidiNote.setText("1", false);
    m_MidiChan.addListener(this); m_MidiChan.setText("1", false);

    addAndMakeVisible(m_Name);
    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
    addAndMakeVisible(m_MidiChan); addAndMakeVisible(m_MidiChanLabel);

    m_Name.setFontSize(18);
    m_MidiChanLabel.setFontSize(12); m_MidiNoteLabel.setFontSize(12);

    m_Name.setText(config.name, juce::NotificationType::dontSendNotification);
    m_MidiChan.setText(juce::String(r_Config.chan), false);
    m_MidiNote.setText(juce::String(r_Config.note), false);
}

void ConfigComponent::paint(juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::bezelColour));
    g.fillRect(getLocalBounds());
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::lcdColour));
    g.fillRect(getLocalBounds().reduced(2));
}

void ConfigComponent::resized()
{
    auto bounds = getLocalBounds().reduced(5);

    m_Name.setBounds(bounds.removeFromTop(24));
    bounds.removeFromTop(2);
    auto note_row = bounds.removeFromTop(LABEL_HEIGHT);
    m_MidiNoteLabel.setBounds(note_row.removeFromLeft(2 + m_MidiNoteLabel.getFont().getStringWidth(m_MidiNoteLabel.getText())));
    note_row.removeFromLeft(5);
    m_MidiNote.setBounds(note_row);

    bounds.removeFromTop(2);

    auto chan_row = bounds.removeFromTop(LABEL_HEIGHT);
    m_MidiChanLabel.setBounds(chan_row.removeFromLeft(2 + m_MidiChanLabel.getFont().getStringWidth(m_MidiChanLabel.getText())));
    chan_row.removeFromLeft(5);
    m_MidiChan.setBounds(chan_row);
}

void ConfigComponent::textEditorReturnKeyPressed(juce::TextEditor&)
{}

void ConfigComponent::textEditorFocusLost(juce::TextEditor&)
{}
