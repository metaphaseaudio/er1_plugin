//
// Created by Matt on 9/27/2020.
//

#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <er1_dsp/Voice.h>
#include "ER1Sound.h"


class ER1Voice
{
public:
    ER1Voice(ER1Sound::Ptr sound);
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition);
    void updateParams();
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);
    void setSampleRate(double sr);

private:
    ER1Sound::Ptr m_Sound;
    meta::ER1::Voice m_Voice;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ER1Voice);
};


