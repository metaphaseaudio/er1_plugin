//
// Created by Matt on 9/17/2020.
//

#include "LCDScreen.h"
#include "../../look_and_feel/ER1Colours.h"
#include "../../fonts/FontLCD.h"

#define BIG_LABEL_PT 18
#define STD_LABEL_PT 10


LCDScreen::LCDScreen(ConfigParams& config)
    : r_Config(config)
    , m_Name("Sound name", "")
    , m_MidiNote("Midi note", "1"), m_MidiNoteLabel("Midi note label", "Note:")
    , m_MidiChan("Midi chan", "1"), m_MidiChanLabel("Midi chan label", "Chan:")
{
    addAndMakeVisible(m_Name);     //addAndMakeVisible(m_NameLabel);
    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
    addAndMakeVisible(m_MidiChan); addAndMakeVisible(m_MidiChanLabel);

    m_Name.setEditable(false, true); m_MidiNote.setEditable(false, true); m_MidiChan.setEditable(false, true);

    m_Name.setJustificationType(juce::Justification::centred);
    m_MidiNote.setJustificationType(juce::Justification::right);
    m_MidiChan.setJustificationType(juce::Justification::right);

    m_Name.onTextChange = [&](){ r_Config.name = m_Name.getText().toStdString(); };
    m_MidiNote.onTextChange = [&]() { r_Config.note = std::min(127, std::max(0, m_MidiNote.getText().getIntValue())); };
    m_MidiChan.onTextChange = [&]() { r_Config.chan = std::min(16, std::max(1, m_MidiChan.getText().getIntValue())); };


    m_Name.setText(config.name, juce::NotificationType::dontSendNotification);
    m_MidiChan.setText(juce::String(r_Config.chan).toStdString(), juce::dontSendNotification);
    m_MidiNote.setText(juce::String(r_Config.note).toStdString(), juce::dontSendNotification);
}

void LCDScreen::paint(juce::Graphics& g)
{
    auto lcdTextColour = getLookAndFeel().findColour(LCDText::ColourIds::textColour).darker(0.1);
    auto font = FontLCD::ArcadeI();
    m_Name.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_Name.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_MidiChanLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiChanLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_MidiNoteLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiNoteLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);


    m_MidiChan.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiChan.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_MidiNote.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiNote.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::bezelColour));
    g.fillRect(getLocalBounds());
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::lcdColour));
    g.fillRect(getLocalBounds().reduced(1));
}

void LCDScreen::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    bounds.removeFromTop(3);

    auto nameBounds = bounds.removeFromTop(BIG_LABEL_PT);
    //m_NameLabel.setBounds(nameBounds.removeFromLeft(2 + m_NameLabel.getFont().getStringWidth(m_NameLabel.getText())));
    m_Name.setBounds(nameBounds);
    bounds.removeFromTop(8);

    const auto noteLabelLength = 10 + m_MidiNoteLabel.getFont().getStringWidth(m_MidiNoteLabel.getText());
    const auto noteLength = 5 + m_MidiNoteLabel.getFont().getStringWidth("0000");
    const auto chanLabelLength = 10 + m_MidiChanLabel.getFont().getStringWidth(m_MidiChanLabel.getText());
    const auto chanLength = 5 + m_MidiChan.getFont().getStringWidth("000");

    auto midiBounds = bounds.removeFromTop(STD_LABEL_PT);

    m_MidiNoteLabel.setBounds(midiBounds.removeFromLeft(noteLabelLength));
    m_MidiNote.setBounds(midiBounds.removeFromLeft(noteLength));

    m_MidiChanLabel.setBounds(midiBounds.removeFromLeft(chanLabelLength));
    m_MidiChan.setBounds(midiBounds.removeFromLeft(chanLength));

}