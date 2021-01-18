//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <JuceHeader.h>
#include <er1_dsp/Voice.h>
#include "SoundParameterBlocks.h"

class ER1Sound
    : public juce::SynthesiserSound
{
public:
    ER1Sound(OscParams osc, AmpParams amp, int midiNoteNumber, int midiChannel=1);
    bool appliesToNote (int midiNoteNumber) override { return midiNoteNumber == m_Note; };
    bool appliesToChannel (int midiChannel) override { return midiChannel == m_Chan; };

    AmpParams amp;
    OscParams osc;

private:
    int m_Note, m_Chan;
};


