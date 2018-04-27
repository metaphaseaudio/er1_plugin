/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <er1_dsp/Oscillator.h>
#include <er1_dsp/Envelope.h>
#include <er1_dsp/Voice.h>

//==============================================================================
/**
*/
class ER1AudioProcessor
    : public juce::AudioProcessor
{
    static constexpr int ER1_VOICE_COUNT = 1;
public:
    //==============================================================================
    ER1AudioProcessor();
    ~ER1AudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    std::vector<juce::AudioParameterChoice*> m_VoiceModType;
    std::vector<juce::AudioParameterFloat*> m_VoiceModDepth;
    std::vector<juce::AudioParameterFloat*> m_VoiceModSpeed;

    meta::ER1::Voice m_Voices[ER1_VOICE_COUNT];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessor)
};
