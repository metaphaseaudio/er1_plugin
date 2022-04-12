//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <er1_dsp/Voice.h>
#include "SoundParameterBlocks.h"

class ER1Sound
    : public juce::SynthesiserSound
{
public:
    ER1Sound(OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int midiChannel=1);
    bool appliesToNote (int midiNoteNumber) override { return midiNoteNumber == config.note; };
    bool appliesToChannel (int midiChannel) override { return midiChannel == config.chan; };

    void printStatus();

    ConfigParams config;
    AmpParams amp;
    OscParams osc;
    DelayParams delay;

private:
};


