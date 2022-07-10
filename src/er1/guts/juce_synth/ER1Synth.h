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
    ER1Voice* addVoice(ER1Voice* voice);
    void prepareToPlay(double sampleRate, int busCount, int blockSize);
    void processBlock(juce::AudioBuffer<float>& audio, juce::MidiBuffer midi, int nSamps, float tempo);
    void triggerVoice(int i);
    [[nodiscard]] const std::vector<std::unique_ptr<ER1Voice>>& getVoices() const { return m_Voices; }


private:
    juce::AudioBuffer<float> m_Tmp;
    std::vector<std::unique_ptr<ER1Voice>> m_Voices;
};


