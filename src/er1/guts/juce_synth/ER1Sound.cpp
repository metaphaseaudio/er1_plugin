//
// Created by Matt on 10/18/2020.
//

#include "ER1Sound.h"

static juce::StringArray OscNames =
{
    "Sine"
    , "Triangle"
};

static juce::StringArray ModulationNames =
{
    "Saw"
    , "Square"
    , "Triangle"
    , "SAH"
    , "Noise"
    , "Decay"
};


ER1Sound::ER1Sound(OscParams osc, AmpParams amp, int midiNoteNumber, int midiChannel)
    : amp(amp)
    , osc(osc)
    , m_Chan(midiChannel)
    , m_Note(midiNoteNumber)
{}
