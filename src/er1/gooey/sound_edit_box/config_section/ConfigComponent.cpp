//
// Created by Matt on 9/17/2020.
//

#include "ConfigComponent.h"
#include "../../look_and_feel/ER1Colours.h"

#define BIG_LABEL_PT 30
#define STD_LABEL_PT 22


ConfigComponent::ConfigComponent(ConfigParams& config)
    : r_Config(config)
    , m_Name("Sound name", "", 9)//, m_NameLabel("Voice label", "", 5)
    , m_MidiNote("Midi note", "1", 3), m_MidiNoteLabel("Midi note label", "Note:", 4)
    , m_MidiChan("Midi chan", "1", 2), m_MidiChanLabel("Midi chan label", "Chan:", 4)
{
    addAndMakeVisible(m_Name);     //addAndMakeVisible(m_NameLabel);
    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
    addAndMakeVisible(m_MidiChan); addAndMakeVisible(m_MidiChanLabel);

    m_Name.setFontSize(BIG_LABEL_PT); //m_NameLabel.setFontSize(BIG_LABEL_PT);
    m_Name.setEditable(false, true); m_MidiNote.setEditable(false, true); m_MidiChan.setEditable(false, true);
    m_Name.setJustificationType(juce::Justification::centred);
    m_MidiNote.setJustificationType(juce::Justification::right);
    m_MidiChan.setJustificationType(juce::Justification::right);

    m_Name.onTextChange = [&](){ r_Config.name = m_Name.getText().toStdString(); };
    m_MidiNote.onTextChange = [&]() { r_Config.note = std::min(127, std::max(0, m_MidiNote.getText().getIntValue())); };
    m_MidiChan.onTextChange = [&]() { r_Config.chan = std::min(16, std::max(1, m_MidiChan.getText().getIntValue())); };
    m_MidiChanLabel.setFontSize(STD_LABEL_PT + 2); m_MidiNoteLabel.setFontSize(STD_LABEL_PT + 2);
    m_MidiChan.setFontSize(STD_LABEL_PT + 2); m_MidiNote.setFontSize(STD_LABEL_PT + 2);

    m_Name.setText(config.name, juce::NotificationType::dontSendNotification);
    m_MidiChan.setText(juce::String(r_Config.chan).toStdString(), juce::dontSendNotification);
    m_MidiNote.setText(juce::String(r_Config.note).toStdString(), juce::dontSendNotification);
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

    auto nameBounds = bounds.removeFromTop(BIG_LABEL_PT);
    //m_NameLabel.setBounds(nameBounds.removeFromLeft(2 + m_NameLabel.getFont().getStringWidth(m_NameLabel.getText())));
    m_Name.setBounds(nameBounds);
    bounds.removeFromTop(5);

    const auto noteLabelLength = 5 + m_MidiNoteLabel.getFont().getStringWidth(m_MidiNoteLabel.getText());
    const auto noteLength = 5 + m_MidiNoteLabel.getFont().getStringWidth("000");
    const auto chanLabelLength = 5 + m_MidiChanLabel.getFont().getStringWidth(m_MidiChanLabel.getText());
    const auto chanLength = 5 + m_MidiChan.getFont().getStringWidth("00");

    auto midiBounds = bounds.removeFromTop(STD_LABEL_PT);

    m_MidiNoteLabel.setBounds(midiBounds.removeFromLeft(noteLabelLength));
    m_MidiNote.setBounds(midiBounds.removeFromLeft(noteLength));

    m_MidiChanLabel.setBounds(midiBounds.removeFromLeft(chanLabelLength));
    m_MidiChan.setBounds(midiBounds.removeFromLeft(chanLength));

}