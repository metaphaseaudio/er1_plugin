//
// Created by Matt on 9/27/2020.
//

#include "ER1VoiceController.h"

ER1Voice::ER1Voice()
    : m_Voice(getSampleRate())
{}

void ER1Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    auto* voice_params = static_cast<ER1Sound*>(getCurrentlyPlayingSound().get());
    m_Voice.setWaveShape(static_cast<meta::ER1::WaveShape>(voice_params->osc.oscType->getIndex()));
    m_Voice.setModulationShape(static_cast<meta::ER1::Voice::ModShape>(voice_params->osc.modType->getIndex()));
    m_Voice.setModulationSpeed(voice_params->osc.modSpeed->get());
    m_Voice.setModulationDepth(voice_params->osc.modDepth->get());
    m_Voice.setPitch(voice_params->osc.pitch->get());
    m_Voice.level = voice_params->amp.level->get();
    m_Voice.setDecay(voice_params->amp.decay->get());

    m_Voice.reset();
    m_Voice.start();
}

void ER1Voice::stopNote(float velocity, bool allowTailOff)
{
    if (!allowTailOff)
    {
        clearCurrentNote();
        m_Voice.reset();
    }
}

void ER1Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (auto* voice_params = static_cast<ER1Sound*> (getCurrentlyPlayingSound().get()))
    {
        // Plus one here to align with the options
        m_Voice.setWaveShape(static_cast<meta::ER1::WaveShape>(voice_params->osc.oscType->getIndex()));
        m_Voice.setModulationShape(static_cast<meta::ER1::Voice::ModShape>(voice_params->osc.modType->getIndex()));
        m_Voice.setModulationSpeed(voice_params->osc.modSpeed->get());
        m_Voice.setModulationDepth(voice_params->osc.modDepth->get());
        m_Voice.setPitch(voice_params->osc.pitch->get());
        m_Voice.level = voice_params->amp.level->get();
        m_Voice.pan = voice_params->amp.pan->get();
        m_Voice.setDecay(voice_params->amp.decay->get());

        m_Voice.processBlock(
            outputBuffer.getArrayOfWritePointers()
            , numSamples
            , startSample
        );

        if (m_Voice.hasEnded())
            { stopNote (0.0f, false); }
    }
}

void ER1Voice::setCurrentPlaybackSampleRate(double newRate)
{
    SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);
    m_Voice.setSampleRate(newRate);
}

bool ER1Voice::canPlaySound(juce::SynthesiserSound* sound)
{
    const auto ref_count = sound->getReferenceCount();
    if (ref_count > 2 && sound != static_cast<juce::SynthesiserSound*>(getCurrentlyPlayingSound()))
        { return false; }
    return true;
}

