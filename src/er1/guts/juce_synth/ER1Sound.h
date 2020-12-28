//
// Created by Matt on 10/18/2020.
//

#pragma once

#include <JuceHeader.h>
#include <er1_dsp/Voice.h>

class ER1Sound
    : public juce::SynthesiserSound
{
public:
    struct OscParams
    {
        juce::AudioParameterChoice& oscType;
        juce::AudioParameterChoice& modType;
        juce::AudioParameterFloat& pitch;
        juce::AudioParameterFloat& modSpeed;
        juce::AudioParameterFloat& modDepth;
    };

    struct AmpParams
    {
        juce::AudioParameterFloat& decay;
        juce::AudioParameterFloat& level;
        juce::AudioParameterFloat& pan;
        juce::AudioParameterFloat& lowBoost;
    };

    bool appliesToNote (int midiNoteNumber) override { return midiNoteNumber == m_Note; };
    bool appliesToChannel (int midiChannel) override { return midiChannel == m_Chan; };

    AmpParams amp_params;
    OscParams osc_params;

private:
    int m_Note, m_Chan;
};


