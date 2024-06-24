//
// Created by Matt on 4/19/2022.
//

#include "ER1Synth.h"
#include <meta/dsp/OversampledBuffer.h>
#include <meta/dsp/LinearResample.h>

ER1Synth::ER1Synth()
    : m_Tmp(3, 44100)
{}

void ER1Synth::processBlock(juce::dsp::AudioBlock<float>& audio, const juce::MidiBuffer& midi, float tempo)
{
    std::vector<float*> tmp;
    for (int c = 0; c < audio.getNumChannels(); c++)
        { tmp.push_back(audio.getChannelPointer(c)); }

    juce::AudioBuffer<float> audioOut;
    audioOut.setDataToReferTo(tmp.data(), audio.getNumChannels(), audio.getNumSamples());

    ///////////////////////////////////////////////////////////////////////////

    bool isSolod = false;
    for (auto& voice : m_Voices)
    {
        voice->updateParams(tempo);
        if (voice->getControlBlock()->config->solo) { isSolod = true;}
    }

    m_Tmp.copyFrom(0, 0, audio.getChannelPointer(0), audio.getNumSamples());
    m_Tmp.copyFrom(1, 0, audio.getChannelPointer(1), audio.getNumSamples());

    audioOut.clear();

    auto nSamps = audio.getNumSamples();

    int startSample = 0;

    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::Downsampler::OverSample - startSample;
        const auto msg = event.getMessage();

        for (int i = 0; i < m_Voices.size(); i++)
        {
            auto& voice = m_Voices[i];

            // Determine if the voice has an output.
            const auto is_ring_modulator = i + 1 < m_Voices.size() && m_Voices[i + 1]->isRingModCarrier();
            auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
            if (isSolod && !voice->getControlBlock()->config->solo) { outData = nullptr; }

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
        const bool is_ring_modulator = ((i + 1) < m_Voices.size()) && m_Voices[i + 1]->isRingModCarrier();
        auto outData = !is_ring_modulator ? audioOut.getArrayOfWritePointers() : nullptr;
        if (isSolod && !voice->getControlBlock()->config->solo) { outData = nullptr; }
        voice->processBlock(m_Tmp.getArrayOfWritePointers(), outData, m_Tmp.getReadPointer(0), toRender, startSample);
    }
}

void ER1Synth::prepareToPlay(double sampleRate, int busCount, int blockSize)
{
    for (auto& voice : m_Voices)
    {
        voice->stop();
        voice->setSampleRate(sampleRate);
        voice->setMaxBusCount(busCount);
    }

    m_Tmp.setSize(3, blockSize);
    m_Tmp.clear();
}

ER1Voice* ER1Synth::addVoice(ER1Voice* voice)
    { return m_Voices.emplace_back(voice).get(); }

void ER1Synth::triggerVoice(int i)
{
    auto& voice = m_Voices[i];
    voice->startNote(64, 1.0f, 0.0f);
}
