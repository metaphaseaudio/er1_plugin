//
// Created by Matt on 9/13/2020.
//

#pragma once
#include <meta/gooey/MidiComponent.h>
#include "KorgButton.h"


class KorgPad
    : public meta::MidiComponent
{
public:
    explicit KorgPad(meta::MidiState& state);
    juce::MidiMessage getMidiMessageForMouseEvent(const juce::MouseEvent& e, bool down) override;
    void handleMessage(const juce::MidiMessage& msg) override;
    void paint(juce::Graphics& g) override;
    char note;
    char chan;

private:
    bool m_padIsLit;
};



