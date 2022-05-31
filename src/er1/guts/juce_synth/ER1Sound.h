//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <er1_dsp/AnalogVoice.h>
#include "SoundParameterBlocks.h"

class ER1Sound
    : public juce::ReferenceCountedObject
{
public:
    using Ptr = juce::ReferenceCountedObjectPtr<ER1Sound>;
    ER1Sound(OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int midiChannel=1);
    bool appliesToNote (int midiNoteNumber) const { return midiNoteNumber == config.note; };
    bool appliesToChannel (int midiChannel) const { return midiChannel == config.chan; };
    bool isRingModCarrier() const { return osc.enableRing != nullptr && osc.enableRing->get(); }
    void printStatus();

    ConfigParams config;
    AmpParams amp;
    OscParams osc;
    DelayParams delay;


};


