//
// Created by Matt on 9/27/2020.
//

#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include <er1_dsp/AnalogVoice.h>
#include "ER1Sound.h"
#include "er1_dsp/Channel.h"


class ER1Voice
{
public:
    ER1Voice(ER1Sound::Ptr sound);
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition);
    void updateParams();
    void setSampleRate(double sr);

    void processVoice(float* outData, const float* lastData, int samps, int offset) { m_Voice.processBlock(outData, lastData, samps, offset); }
    void processChannel(const float* inData, float** outData, int samps, int offset) { m_Channel.processBlock(inData, outData, samps, offset); }

private:
    ER1Sound::Ptr m_Sound;
    meta::ER1::AnalogVoice m_Voice;
    meta::ER1::Channel m_Channel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ER1Voice);
};


