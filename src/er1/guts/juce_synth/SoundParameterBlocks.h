//
// Created by Matt on 12/29/2020.
//

#pragma once
#include <JuceHeader.h>


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


