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
    for (auto& voice : m_Voices) { voice->updateParams(); }

    nSamps *= meta::ER1::MainOscillator::OverSample;
    int startSample = 0;

    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::MainOscillator::OverSample - startSample;
        const auto msg = event.getMessage();

        for (int i = 0; i < m_Voices.size(); i++)
        {
            auto& voice = m_Voices[i];
            const auto& sound = m_Sounds[i];
            const auto is_ring_modulator = i + 1 < m_Sounds.size() && m_Sounds[i + 1]->isRingModCarrier();
            const auto* ringData = sound->isRingModCarrier() ? m_Tmp.getReadPointer(0) : nullptr;
            auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
            voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);

            voice->processChannel(m_Tmp.getReadPointer(0), outData, toRender, startSample);

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
        const auto* ringData = m_Sounds[i]->isRingModCarrier() ? m_Tmp.getReadPointer(0) : nullptr;
        const auto is_ring_modulator = i + 1 < m_Sounds.size() && m_Sounds[i + 1]->isRingModCarrier();
        auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;

        voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);
        voice->processChannel(m_Tmp.getReadPointer(0), outData, toRender, startSample);
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
