//
// Created by Matt on 9/27/2020.
//

#include "ER1VoiceController.h"

void ER1Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    auto* voice_params = static_cast<ER1Sound*> (getCurrentlyPlayingSound().get());
    m_Voice.oscillator.waveType = static_cast<meta::ER1::Oscillator::WaveType>(voice_params->osc.oscType->getIndex() + 1);
    m_Voice.setModulationType(static_cast<meta::ER1::Voice::ModType>(voice_params->osc.modType->getIndex()));
    m_Voice.setModulationSpeed(voice_params->osc.modSpeed->get());
    m_Voice.setModulationDepth(voice_params->osc.modDepth->get());
    m_Voice.setPitch(voice_params->osc.pitch->get());
    m_Voice.level = voice_params->amp.level->get();
    m_Voice.envelope.setSpeed(voice_params->amp.decay->get());

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
        m_Voice.oscillator.waveType = static_cast<meta::ER1::Oscillator::WaveType>(voice_params->osc.oscType->getIndex() + 1);
        m_Voice.setModulationType(static_cast<meta::ER1::Voice::ModType>(voice_params->osc.modType->getIndex()));
        m_Voice.setModulationSpeed(voice_params->osc.modSpeed->get());
        m_Voice.setModulationDepth(voice_params->osc.modDepth->get());
        m_Voice.setPitch(voice_params->osc.pitch->get());
        m_Voice.level = voice_params->amp.level->get();
        m_Voice.pan = voice_params->amp.pan->get();
        m_Voice.envelope.setSpeed(voice_params->amp.decay->get());

        m_Voice.processBlock(
            outputBuffer.getArrayOfWritePointers()
            , numSamples
            , startSample
        );

        if (m_Voice.envelope.hasEnded())
            { stopNote (0.0f, false); }
    }
}
