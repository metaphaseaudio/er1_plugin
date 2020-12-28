//
// Created by Matt on 9/27/2020.
//

#pragma once
#include <JuceHeader.h>
#include <er1_dsp/Voice.h>
#include "ER1Sound.h"


class ER1Voice
    : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound*) override { return true; }
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override {};
    void controllerMoved(int controllerNumber, int newControllerValue) override {};
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
private:
    meta::ER1::Voice& m_Voice;
};


