//
// Created by Matt on 12/29/2020.
//

#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

struct ConfigParams
{
    std::string name = "New Sound";
    std::atomic<unsigned int> note = 1;
    std::atomic<unsigned int> chan = 1;
};

struct OscParams
{
    juce::AudioParameterChoice* oscType;
    juce::AudioParameterChoice* modType;
    juce::AudioParameterFloat* pitch;
    juce::AudioParameterFloat* modSpeed;
    juce::AudioParameterFloat* modDepth;
};

struct AmpParams
{
    juce::AudioParameterFloat* decay;
    juce::AudioParameterFloat* level;
    juce::AudioParameterFloat* pan;
    juce::AudioParameterFloat* lowBoost;
};

struct DelayParams
{
    juce::AudioParameterFloat* time;
    juce::AudioParameterFloat* depth;
    juce::AudioParameterBool* sync;
};
