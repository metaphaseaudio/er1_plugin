//
// Created by Matt on 4/19/2022.
//

#include "ER1Synth.h"
#include "meta/dsp/OversampledBuffer.h"

ER1Synth::ER1Synth()
    : m_Tmp(2, 44100)
    , m_CurrentPitchPosition(0)
{}


void ER1Synth::processBlock(juce::AudioBuffer<float>& audioOut, juce::MidiBuffer midi, int nSamps)
{
    nSamps *= meta::ER1::MainOscillator::OverSample;
    int startSample = 0;

    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::MainOscillator::OverSample - startSample;
        const auto msg = event.getMessage();

        for (int i = 0; i < m_Voices.size(); i++)
        {
            auto& voice = m_Voices[i];

            const auto* ringData = m_Sounds[i]->enableRing ? m_Tmp.getReadPointer(0) : nullptr;
            voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);
            voice->processChannel(m_Tmp.getReadPointer(0), audioOut.getArrayOfWritePointers(), toRender, startSample);


            const auto& sound =  m_Sounds[i];

            if (msg.isNoteOn())
            {
                if (sound->appliesToChannel(msg.getChannel()) && sound->appliesToNote(msg.getNoteNumber()))
                    { voice->startNote(msg.getNoteNumber(), msg.getFloatVelocity(), 0); }
            }
        }

        startSample += toRender;
    }

    const auto toRender = nSamps - startSample;

    // Finish the remaining samples
    for (int i = 0; i < m_Voices.size(); i++)
    {
        auto& voice = m_Voices[i];
        const auto* ringData = m_Sounds[i]->enableRing ? m_Tmp.getReadPointer(0) : nullptr;
        voice->updateParams();
        voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);
        voice->processChannel(m_Tmp.getReadPointer(0), audioOut.getArrayOfWritePointers(), toRender, startSample);
    }
}


void ER1Synth::addSound(ER1Sound::Ptr& sound)
{
    m_Sounds.add(sound);
    m_Voices.emplace_back(new ER1Voice(sound));
}

void ER1Synth::prepareToPlay(double sampleRate, int blockSize)
{
    for (auto& voice : m_Voices)
        { voice->setSampleRate(sampleRate * meta::ER1::Downsampler::OverSample); }

    m_Tmp.setSize(1, blockSize * meta::ER1::Downsampler::OverSample);
    m_Tmp.clear();
}
