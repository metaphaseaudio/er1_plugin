//
// Created by Matt on 9/17/2020.
//

#include "LCDScreen.h"
#include "../../look_and_feel/ER1Colours.h"
#include "../../fonts/FontLCD.h"

#define BIG_LABEL_PT 17
#define STD_LABEL_PT 12


LCDScreen::LCDScreen(ER1SoundPatch& config)
    : r_LivePatch(config), m_NoteFollow("follow"), m_Solo("solo"), m_Mute("mute")
    , m_Name("Sound name", ""), m_NameLabel("Sound Name Label", "Snd:")
    , m_MidiNote("Midi note", "1"), m_MidiNoteLabel("Midi note label", "Note:")
    , m_MidiChan("Midi chan", "1"), m_MidiChanLabel("Midi chan label", "Chan:")
    , m_AudioBus("Audio bus", "0"), m_AudioBusLabel("Audio bus", "Bus:")
{
    addAndMakeVisible(m_Name);     addAndMakeVisible(m_NameLabel);
    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
    addAndMakeVisible(m_MidiChan); addAndMakeVisible(m_MidiChanLabel);
    addAndMakeVisible(m_AudioBus); addAndMakeVisible(m_AudioBusLabel);
    addAndMakeVisible(m_NoteFollow);
    addAndMakeVisible(m_Solo);
    addAndMakeVisible(m_Mute);

    m_Name.setEditable(false, true); m_MidiNote.setEditable(false, true); m_MidiChan.setEditable(false, true); m_AudioBus.setEditable(false, true);

    m_MidiNote.setJustificationType(juce::Justification::right);
    m_MidiChan.setJustificationType(juce::Justification::right);
    m_AudioBus.setJustificationType(juce::Justification::right);

    m_Name.onTextChange = [&](){
        r_LivePatch.setPatchName(m_Name.getText().toStdString());
    };

    m_MidiNote.onTextChange = [&](){
        r_LivePatch.config.note = std::min(127, std::max(0, m_MidiNote.getText().getIntValue()));
        m_MidiNote.setText(juce::String(r_LivePatch.config.note), juce::dontSendNotification);
    };

    m_MidiChan.onTextChange = [&](){
        r_LivePatch.config.chan = std::min(16, std::max(1, m_MidiChan.getText().getIntValue()));
        m_MidiChan.setText(juce::String(r_LivePatch.config.chan), juce::dontSendNotification);
    };

    m_AudioBus.onTextChange = [&](){
        r_LivePatch.config.bus = std::min(meta::ER1::NumOutBuses - 1, std::max(0, m_AudioBus.getText().getIntValue()));
        m_AudioBus.setText(juce::String(r_LivePatch.config.bus), juce::dontSendNotification);
    };

    m_NoteFollow.setToggleState(r_LivePatch.config.noteFollow, juce::dontSendNotification);
    m_NoteFollow.onClick = [&]()
        { r_LivePatch.config.noteFollow = !r_LivePatch.config.noteFollow; };

    m_Mute.setToggleState(r_LivePatch.config.mute, juce::dontSendNotification);
    m_Mute.onClick = [&]()
        { r_LivePatch.config.mute = !r_LivePatch.config.mute; };

    m_Solo.setToggleState(r_LivePatch.config.solo, juce::dontSendNotification);
    m_Solo.onClick = [&]()
        { r_LivePatch.config.solo = !r_LivePatch.config.solo; };

    refreshText(juce::dontSendNotification);
}

void LCDScreen::paint(juce::Graphics& g)
{
    refreshText(juce::dontSendNotification);
    auto lcdTextColour = getLookAndFeel().findColour(LCDText::ColourIds::textColour).darker(0.1);
    auto& font = FontLCD::defaultFont();

    m_NameLabel.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_NameLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);
    m_Name.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_Name.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_MidiChanLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiChanLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);
    m_MidiChan.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiChan.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_MidiNoteLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiNoteLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);
    m_MidiNote.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiNote.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    m_AudioBusLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_AudioBusLabel.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);
    m_AudioBus.setFont(font.withPointHeight(STD_LABEL_PT));
    m_AudioBus.setColour(juce::Label::ColourIds::textColourId, lcdTextColour);

    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::bezelColour));
    g.fillRect(getLocalBounds());
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::lcdColour));
    g.fillRect(getLocalBounds().reduced(1));
}

void LCDScreen::resized()
{
    auto bounds = getLocalBounds().reduced(1);
    bounds.removeFromTop(3);

    bounds.removeFromTop(BIG_LABEL_PT); // Bank Name
    bounds.removeFromTop(4);

    auto nameBounds = bounds.removeFromTop(BIG_LABEL_PT);

    const auto nameLabelLength = juce::Rectangle<int>(
        nameBounds.getX(), nameBounds.getY(),
        BIG_LABEL_PT + m_NameLabel.getFont().getStringWidthFloat(m_NameLabel.getText()) + 5, nameBounds.getHeight()
    );

    const auto nameLength = juce::Rectangle<int>(
        nameLabelLength.getRight() - 8, nameBounds.getY(),
        nameBounds.getWidth() - (nameBounds.getY() + BIG_LABEL_PT), nameBounds.getHeight()
    );

    bounds.removeFromTop(2);

    auto midiBounds = bounds.removeFromTop(STD_LABEL_PT);

    const auto noteLabelLength = juce::Rectangle<int>(
        midiBounds.getX(), midiBounds.getY(),
        STD_LABEL_PT + m_MidiNoteLabel.getFont().getStringWidthFloat(m_MidiNoteLabel.getText()), midiBounds.getHeight()
    );
    const auto noteLength = juce::Rectangle<int>(
        noteLabelLength.getRight() - STD_LABEL_PT, midiBounds.getY(),
        STD_LABEL_PT + m_MidiNoteLabel.getFont().getStringWidthFloat("000"), midiBounds.getHeight()
    );

    const auto chanLabelLength = juce::Rectangle<int>(
        noteLength.getRight() + 2, midiBounds.getY(),
        STD_LABEL_PT + m_MidiChanLabel.getFont().getStringWidthFloat(m_MidiChanLabel.getText()), midiBounds.getHeight()
    );
    const auto chanLength = juce::Rectangle<int>(
        chanLabelLength.getRight() - STD_LABEL_PT, midiBounds.getY(),
        STD_LABEL_PT + m_MidiChan.getFont().getStringWidthFloat("00"), midiBounds.getHeight()
    );

    const auto audioLabelLength = juce::Rectangle<int>(
        chanLength.getRight() + 2, midiBounds.getY(),
        STD_LABEL_PT + m_AudioBusLabel.getFont().getStringWidthFloat(m_AudioBusLabel.getText()), midiBounds.getHeight()
    );
    const auto audioLength = juce::Rectangle<int>(
        audioLabelLength.getRight() - STD_LABEL_PT, midiBounds.getY(),
        STD_LABEL_PT + m_AudioBus.getFont().getStringWidthFloat("00"), midiBounds.getHeight()
    );

    m_NameLabel.setBounds(nameLabelLength); m_Name.setBounds(nameLength);
    m_MidiNoteLabel.setBounds(noteLabelLength); m_MidiNote.setBounds(noteLength);
    m_MidiChanLabel.setBounds(chanLabelLength); m_MidiChan.setBounds(chanLength);
    m_AudioBusLabel.setBounds(audioLabelLength); m_AudioBus.setBounds(audioLength);

    bounds.removeFromTop(3);
    bounds.removeFromLeft(15);
    auto otherCtrlBounds = bounds.removeFromTop(12);

    m_NoteFollow.setBounds(otherCtrlBounds.removeFromLeft(58));
    otherCtrlBounds.removeFromLeft(2);
    m_Mute.setBounds(otherCtrlBounds.removeFromLeft(58));
    otherCtrlBounds.removeFromLeft(2);
    m_Solo.setBounds(otherCtrlBounds.removeFromLeft(58));
}

void LCDScreen::refreshText(juce::NotificationType notify)
{
    if (!m_Name.isBeingEdited()) { m_Name.setText(r_LivePatch.getPatchName(), notify); }
    if (!m_MidiChan.isBeingEdited()) { m_MidiChan.setText(juce::String(r_LivePatch.config.chan).toStdString(), notify); }
    if (!m_MidiNote.isBeingEdited()) { m_MidiNote.setText(juce::String(r_LivePatch.config.note).toStdString(), notify); }
    if (!m_AudioBus.isBeingEdited()) { m_AudioBus.setText(juce::String(r_LivePatch.config.bus).toStdString(), notify); }
}
