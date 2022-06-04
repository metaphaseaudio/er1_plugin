//
// Created by Matt on 4/19/2022.
//

#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "ER1Voice.h"
#include "ER1ControlBlock.h"


class ER1Synth
{
public:
    ER1Synth();
    void addVoice(ER1Voice* voice);
    void prepareToPlay(double sampleRate, int blockSize);
    void processBlock(juce::AudioBuffer<float>& audio, juce::MidiBuffer midi, int nSamps);

private:
    juce::AudioBuffer<float> m_Tmp;
    std::vector<std::unique_ptr<ER1Voice>> m_Voices;
};


