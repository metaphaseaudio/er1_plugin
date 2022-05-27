//
// Created by Matt on 4/19/2022.
//

#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "ER1VoiceController.h"
#include "ER1Sound.h"


class ER1Synth
{
public:
    ER1Synth();
    void addSound(ER1Sound::Ptr& sound);
    void prepareToPlay(double sampleRate, int blockSize);
    void processBlock(juce::AudioBuffer<float>& audio, juce::MidiBuffer midi, int nSamps);

private:
    juce::AudioBuffer<float> m_Tmp;

    int m_CurrentPitchPosition;

    juce::ReferenceCountedArray<ER1Sound> m_Sounds;
    std::vector<std::unique_ptr<ER1Voice>> m_Voices;
};


