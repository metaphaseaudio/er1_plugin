//
// Created by Matt on 4/19/2022.
//

#include "ER1Synth.h"
#include <meta/dsp/OversampledBuffer.h>
#include <meta/dsp/LinearResample.h>

ER1Synth::ER1Synth()
    : m_Tmp(2, 44100)
{}


void ER1Synth::processBlock(juce::AudioBuffer<float>& audioOut, juce::MidiBuffer midi, int nSamps)
{
    for (auto& voice : m_Voices) { voice->updateParams(); }

    // Up-sample by linear interpolation the incoming audio
    for (int c = audioOut.getNumChannels(); --c >= 0;)
        { meta::linearUpsample(audioOut.getReadPointer(c), audioOut.getWritePointer(c), nSamps, nSamps * meta::ER1::MainOscillator::OverSample); }

    nSamps *= meta::ER1::MainOscillator::OverSample;

    int startSample = 0;

    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::MainOscillator::OverSample - startSample;
        const auto msg = event.getMessage();

        for (int i = 0; i < m_Voices.size(); i++)
        {
            auto& voice = m_Voices[i];
            const auto is_ring_modulator = i + 1 < m_Voices.size() && m_Voices[i + 1]->getSound()->isRingModCarrier();
            const auto* ringData = voice->getSound()->isRingModCarrier() ? m_Tmp.getReadPointer(0) : nullptr;
            auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
            voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);

            voice->processChannel(m_Tmp.getReadPointer(0), outData, toRender, startSample);

            if (msg.isNoteOn())
            {
                if (voice->getSound()->appliesToChannel(msg.getChannel()) && voice->getSound()->appliesToNote(msg.getNoteNumber()))
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
        const auto* ringData = voice->getSound()->isRingModCarrier() ? m_Tmp.getReadPointer(0) : nullptr;
        const auto is_ring_modulator = i + 1 < m_Voices.size() && m_Voices[i + 1]->getSound()->isRingModCarrier();
        auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;

        voice->processVoice(m_Tmp.getWritePointer(0), ringData, toRender, startSample);
        voice->processChannel(m_Tmp.getReadPointer(0), outData, toRender, startSample);
    }
}


void ER1Synth::addSound(ER1Sound* sound)
    { m_Voices.emplace_back(new ER1Voice(sound)); }

void ER1Synth::prepareToPlay(double sampleRate, int blockSize)
{
    for (auto& voice : m_Voices)
        { voice->setSampleRate(sampleRate * meta::ER1::Downsampler::OverSample); }

    m_Tmp.setSize(1, blockSize * meta::ER1::Downsampler::OverSample);
    m_Tmp.clear();
}
