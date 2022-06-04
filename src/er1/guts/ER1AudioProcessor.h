/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <er1_dsp/Constants.h>
#include <er1_dsp/Envelope.h>
#include <meta/midi/MidiState.h>
#include "juce_synth/ER1Synth.h"
#include "juce_synth/ER1ControlBlock.h"
#include "juce_synth/ER1Voice.h"

//==============================================================================
/**
*/
class ER1AudioProcessor
    : public juce::AudioProcessor
{
public:
#ifdef _DEBUG
    static constexpr int ANALOG_SOUND_COUNT = 3;
#else
    static constexpr int ANALOG_SOUND_COUNT = 10;
#endif

    static constexpr int AUDIO_SOUND_COUNT = 2;
    static constexpr int ER1_SOUND_COUNT = ANALOG_SOUND_COUNT + AUDIO_SOUND_COUNT;
    //==============================================================================
    ER1AudioProcessor();
    ~ER1AudioProcessor() override = default;

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

    meta::MidiState& getMidiState() { return m_MidiState; }
    ER1ControlBlock::Ptr getSound(int i) { return m_Sounds[i]; }
    void triggerVoice(int num);
    juce::ReferenceCountedArray<ER1ControlBlock>& getAllSounds() { return m_Sounds; }

private:
    void addAnalogVoice(int voiceNumber, bool canBeRingCarrier);
    void addAudioVoice(int voiceNumber, bool canBeRingCarrier);
    void addPCMVoice(int voiceNumber);

    meta::MidiState m_MidiState;
    juce::ReferenceCountedArray<ER1ControlBlock> m_Sounds;
    ER1Synth m_Synth;

    std::vector<juce::MidiMessage> m_QueuedMessages;
    juce::AudioBuffer<float> m_OversampleBuffer;
    meta::ER1::Downsampler m_Downsampler;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessor)
};
