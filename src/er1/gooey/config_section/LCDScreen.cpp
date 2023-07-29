//
// Created by Matt on 9/17/2020.
//

#include "LCDScreen.h"
#include "../look_and_feel/ER1Colours.h"
#include "../fonts/FontLCD.h"

static constexpr float BIG_LABEL_PT = 22.0f;
static constexpr float STD_LABEL_PT = 18.0f;


LCDScreen::LCDScreen()
    : p_LivePatch(nullptr), m_NoteFollow("follow"), m_Solo("solo"), m_Mute("mute")
    , m_Name("Sound name", ""), m_NameLabel("Sound Name Label", "SOUND:")
    , m_MidiNote(juce::Slider::SliderStyle::LinearBarVertical, juce::Slider::TextEntryBoxPosition::TextBoxBelow), m_MidiNoteLabel("Midi note label", "NOTE:")
    , m_MidiChan(juce::Slider::SliderStyle::LinearBarVertical, juce::Slider::TextEntryBoxPosition::TextBoxBelow), m_MidiChanLabel("Midi chan label", "CHAN:")
    , m_AudioBus(juce::Slider::SliderStyle::LinearBarVertical, juce::Slider::TextEntryBoxPosition::TextBoxBelow), m_AudioBusLabel("Audio bus", "BUS:")
{
    addAndMakeVisible(m_Name);     addAndMakeVisible(m_NameLabel);
    addAndMakeVisible(m_MidiNote); addAndMakeVisible(m_MidiNoteLabel);
    addAndMakeVisible(m_MidiChan); addAndMakeVisible(m_MidiChanLabel);
    addAndMakeVisible(m_AudioBus); addAndMakeVisible(m_AudioBusLabel);
    addAndMakeVisible(m_NoteFollow);
    addAndMakeVisible(m_Solo);
    addAndMakeVisible(m_Mute);

    m_MidiNote.setSliderSnapsToMousePosition(false);
    m_MidiChan.setSliderSnapsToMousePosition(false);
    m_AudioBus.setSliderSnapsToMousePosition(false);

    m_MidiNote.setRange(1, 127, 1);
    m_MidiChan.setRange(1, 16, 1);
    m_AudioBus.setRange(0, meta::ER1::NumOutBuses, 1);

    m_Name.setEditable(false, true);

    m_Name.onTextChange = [&](){
        p_LivePatch->setPatchName(m_Name.getText().toStdString());
    };

    m_MidiNote.onValueChange = [&](){
        p_LivePatch->config.note = int(std::min(127.0, std::max(0.0, m_MidiNote.getValue())));
    };

    m_MidiChan.onValueChange = [&](){
        p_LivePatch->config.chan = int(std::min(16.0, std::max(1.0, m_MidiChan.getValue())));
    };

    m_AudioBus.onValueChange = [&](){
        p_LivePatch->config.bus = int(std::min(meta::ER1::NumOutBuses - 1.0, std::max(0.0, m_AudioBus.getValue())));
    };

    m_NoteFollow.onClick = [&]()
        { p_LivePatch->config.noteFollow = !p_LivePatch->config.noteFollow; };

    m_Mute.onClick = [&]()
        { p_LivePatch->config.mute = !p_LivePatch->config.mute; };

    m_Solo.onClick = [&]()
        { p_LivePatch->config.solo = !p_LivePatch->config.solo; };

    refreshText(juce::dontSendNotification);
}

void LCDScreen::paint(juce::Graphics& g)
{
    refreshText(juce::dontSendNotification);
    auto& font = FontLCD::defaultFont();
    m_NameLabel.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_Name.setFont(font.withPointHeight(BIG_LABEL_PT));
    m_MidiChanLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_MidiNoteLabel.setFont(font.withPointHeight(STD_LABEL_PT));
    m_AudioBusLabel.setFont(font.withPointHeight(STD_LABEL_PT));
}

void LCDScreen::resized()
{
    const auto& font = FontLCD::defaultFont();
    auto bounds = getLocalBounds();
    bounds.removeFromTop(26); // Bank Name
    bounds.removeFromTop(4);

    auto nameBounds = bounds.removeFromTop(BIG_LABEL_PT);

    const auto nameLabelLength = juce::Rectangle<int>(
        nameBounds.getX(), nameBounds.getY(),
        int(BIG_LABEL_PT + m_NameLabel.getFont().getStringWidthFloat(m_NameLabel.getText() + "   ") + 5.0f), nameBounds.getHeight()
    );

    const auto nameLength = juce::Rectangle<int>(
        nameLabelLength.getRight() - 8, nameBounds.getY(),
        nameBounds.getWidth() - (nameBounds.getY() + BIG_LABEL_PT), nameBounds.getHeight()
    );

    bounds.removeFromTop(2);

    auto midiBounds = bounds.removeFromTop(STD_LABEL_PT);

    const auto noteLabelLength = juce::Rectangle<int>(
        midiBounds.getX(), midiBounds.getY(),
        STD_LABEL_PT + m_MidiNoteLabel.getFont().getStringWidthFloat(m_MidiNoteLabel.getText() + "00"), midiBounds.getHeight()
    );

    const auto noteBounds = juce::Rectangle<int>(
        noteLabelLength.getRight() - STD_LABEL_PT, midiBounds.getY(),
        STD_LABEL_PT + font.getStringWidthFloat("000"), midiBounds.getHeight()
    );

    const auto chanLabelLength = juce::Rectangle<int>(
            noteBounds.getRight() + 2, midiBounds.getY(),
        STD_LABEL_PT + m_MidiChanLabel.getFont().getStringWidthFloat(m_MidiChanLabel.getText() + "00"), midiBounds.getHeight()
    );

    const auto chanBounds = juce::Rectangle<int>(
        chanLabelLength.getRight() - STD_LABEL_PT, midiBounds.getY(),
        STD_LABEL_PT + font.getStringWidthFloat("00"), midiBounds.getHeight()
    );

    const auto audioLabelLength = juce::Rectangle<int>(
            chanBounds.getRight() + 2, midiBounds.getY(),
        STD_LABEL_PT + m_AudioBusLabel.getFont().getStringWidthFloat(m_AudioBusLabel.getText() + "00"), midiBounds.getHeight()
    );

    const auto audioBounds = juce::Rectangle<int>(
        int(audioLabelLength.getRight() - STD_LABEL_PT), midiBounds.getY(),
        int(STD_LABEL_PT + font.getStringWidthFloat("00")), midiBounds.getHeight()
    );

    m_NameLabel.setBounds(nameLabelLength); m_Name.setBounds(nameLength);
    m_MidiNoteLabel.setBounds(noteLabelLength); m_MidiNote.setBounds(noteBounds);
    m_MidiChanLabel.setBounds(chanLabelLength); m_MidiChan.setBounds(chanBounds);
    m_AudioBusLabel.setBounds(audioLabelLength); m_AudioBus.setBounds(audioBounds);

    auto buttonRow = bounds.removeFromBottom(14);
    const auto buttonWidth = (buttonRow.getWidth() - 4.0) * 0.33f;

    m_NoteFollow.setBounds(buttonRow.removeFromLeft(buttonWidth));
    buttonRow.removeFromLeft(2);
    m_Mute.setBounds(buttonRow.removeFromLeft(buttonWidth));
    buttonRow.removeFromLeft(2);
    m_Solo.setBounds(buttonRow.removeFromLeft(buttonWidth));
}

void LCDScreen::refreshText(juce::NotificationType notify)
{
    if (!p_LivePatch) { return; }
    if (!m_Name.isBeingEdited()) { m_Name.setText(p_LivePatch->getPatchName(), notify); }

    m_MidiChan.setValue(p_LivePatch->config.chan, notify);
    m_MidiNote.setValue(p_LivePatch->config.note, notify);
    m_AudioBus.setValue(p_LivePatch->config.bus, notify);
}

void LCDScreen::setPatch(ER1SoundPatch *newPatch)
{
    p_LivePatch = newPatch;
    m_NoteFollow.setToggleState(p_LivePatch->config.noteFollow, juce::dontSendNotification);
    m_Mute.setToggleState(p_LivePatch->config.mute, juce::dontSendNotification);
    m_Solo.setToggleState(p_LivePatch->config.solo, juce::dontSendNotification);
    refreshText(juce::dontSendNotification);
}

