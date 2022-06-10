//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include "SoundParameterBlocks.h"

class ER1ControlBlock
    : public juce::ReferenceCountedObject
{
public:
    using Ptr = juce::ReferenceCountedObjectPtr<ER1ControlBlock>;
    ER1ControlBlock(OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int midiChannel=1);
    bool isRingModCarrier() const { return osc.enableRing != nullptr && osc.enableRing->get(); }
    void printStatus();

    json asJSON() const;
    void fromJSON(json j);

    ConfigParams config;
    AmpParams amp;
    OscParams osc;
    DelayParams delay;

};

