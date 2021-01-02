//
// Created by Matt on 9/27/2020.
//

#include "ER1VoiceController.h"

void ER1Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    auto voice_params = dynamic_cast<ER1Sound*>(sound);
//    m_Voice.setModulationType(0);
    m_Voice.setModulationSpeed(voice_params->osc.modSpeed->get());
    m_Voice.setModulationDepth(voice_params->osc.modDepth->get());
    m_Voice.setPitch(voice_params->osc.pitch->get());
}

void ER1Voice::stopNote(float velocity, bool allowTailOff)
{

}

void ER1Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

}
