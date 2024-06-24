//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include "SoundParameterBlocks.h"
#include "../Patch.h"


class ER1SoundPatch
    : public juce::ReferenceCountedObject
    , public JSONPatch
{
public:
    using Ptr = juce::ReferenceCountedObjectPtr<ER1SoundPatch>;
    ER1SoundPatch(std::string name, OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int midiChannel=1);
    bool isRingModCarrier() const { return osc.enableRing != nullptr && osc.enableRing->get(); }
    void printStatus();

    ConfigParams* config;
    AmpParams amp;
    OscParams osc;
    DelayParams delay;

private:
    json toJsonInternal() const override;
    void fromJsonInternal(const json& j) override;
};


