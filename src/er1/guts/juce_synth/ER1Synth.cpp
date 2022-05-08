//
// Created by Matt on 4/19/2022.
//

#include "ER1Synth.h"
#include "meta/dsp/OversampledBuffer.h"

ER1Synth::ER1Synth()
    : m_Downsampler(48000)
{}


void ER1Synth::processBlock(juce::AudioBuffer<float>& audioIn, juce::MidiBuffer midi)
{
    for (auto& voice : m_Voices)
        { voice->updateParams(); }

    auto audioOut = juce::AudioBuffer<float>(2, audioIn.getNumSamples() * meta::ER1::MainOscillator::OverSample);
    audioOut.clear();

    int startSample = 0;
    for (const auto event : midi)
    {
        const int toRender = event.samplePosition * meta::ER1::MainOscillator::OverSample - startSample;
        const auto msg = event.getMessage();

        for (auto i_voice : meta::enumerate(m_Voices))
        {
            auto& voice = std::get<1>(i_voice);
            const auto& sound =  m_Sounds[std::get<0>(i_voice)];
            voice->renderNextBlock(audioOut, startSample , toRender);

            if (msg.isNoteOn())
            {
                if (sound->appliesToChannel(msg.getChannel()) && sound->appliesToNote(msg.getNoteNumber()))
                    { voice->startNote(msg.getNoteNumber(), msg.getFloatVelocity(), 0); }
            }
        }

        startSample += toRender;
    }

    // Finish the remaining samples
    for (auto& voice : m_Voices)
        { voice->renderNextBlock(audioOut, startSample, audioOut.getNumSamples() - startSample); }

    audioIn.clear();
    m_Downsampler.downsampleBuffer(audioOut, audioIn);
}

void ER1Synth::setSampleRate(double sr)
{
    m_Downsampler.set_sample_rate(sr);
    for (auto& voice : m_Voices)
        { voice->setSampleRate(sr * meta::ER1::Downsampler::OverSample); }
}

void ER1Synth::addSound(ER1Sound::Ptr& sound)
{
    m_Sounds.add(sound);
    m_Voices.emplace_back(new ER1Voice(sound));
}
