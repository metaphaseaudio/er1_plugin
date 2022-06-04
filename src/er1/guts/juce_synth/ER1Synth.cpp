//
// Created by Matt on 4/19/2022.
//

#include "ER1Synth.h"
#include <meta/dsp/OversampledBuffer.h>
#include <meta/dsp/LinearResample.h>

ER1Synth::ER1Synth()
    : m_Tmp(3, 44100)
{}


void ER1Synth::processBlock(juce::AudioBuffer<float>& audioOut, juce::MidiBuffer midi, int nSamps)
{
    for (auto& voice : m_Voices) { voice->updateParams(); }

    // Up-sample by linear interpolation the incoming audio
    for (int c = audioOut.getNumChannels(); --c >= 0;)
    {
        // Copy the data into temp storage chans 1, 2
        meta::linearUpsample(audioOut.getReadPointer(c), m_Tmp.getWritePointer(c + 1), nSamps, nSamps * meta::ER1::MainOscillator::OverSample);
    }

    audioOut.clear();

    nSamps *= meta::ER1::MainOscillator::OverSample;

    int startSample = 0;

    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::MainOscillator::OverSample - startSample;
        const auto msg = event.getMessage();

        for (int i = 0; i < m_Voices.size(); i++)
        {
            auto& voice = m_Voices[i];
            const auto is_ring_modulator = i + 1 < m_Voices.size() && m_Voices[i + 1]->isRingModCarrier();
            auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
            voice->processBlock(m_Tmp.getArrayOfWritePointers(), outData, m_Tmp.getReadPointer(0), toRender, startSample);

            if (msg.isNoteOn())
            {
                if (voice->appliesToChannel(msg.getChannel()) && voice->appliesToNote(msg.getNoteNumber()))
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
        const auto is_ring_modulator = i + 1 < m_Voices.size() && m_Voices[i + 1]->isRingModCarrier();
        auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
        voice->processBlock(m_Tmp.getArrayOfWritePointers(), outData, m_Tmp.getReadPointer(0), toRender, startSample);
    }
}

void ER1Synth::prepareToPlay(double sampleRate, int blockSize)
{
    for (auto& voice : m_Voices)
        { voice->setSampleRate(sampleRate * meta::ER1::Downsampler::OverSample); }

    m_Tmp.setSize(3, blockSize * meta::ER1::Downsampler::OverSample);
    m_Tmp.clear();
}

void ER1Synth::addVoice(ER1Voice* voice)
    { m_Voices.emplace_back(voice); }
