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
#include "MidiManager.h"

//==============================================================================
/**
*/
class ER1AudioProcessor
    : public juce::AudioProcessor
{
public:
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

    MidiManager& getMidiManager() { return m_MidiManager; }
    ER1ControlBlock::Ptr getSound(int i) { return m_CtrlBlocks[i]; }
    void triggerVoice(int num);
    juce::ReferenceCountedArray<ER1ControlBlock>& getAllSounds() { return m_CtrlBlocks; }

private:
    static BusesProperties makeBusesProperties(int inBusses, int outBusses);

    void addMidiLearn(ER1ControlBlock* ctrls);
    void addAnalogVoice(int voiceNumber, bool canBeRingCarrier);
    void addAudioVoice(int voiceNumber, bool canBeRingCarrier);
    ER1Voice* addPCMVoice(std::string name, const char* data, const int nData, float dataSampleRate);

    MidiManager m_MidiManager;

    juce::ReferenceCountedArray<ER1ControlBlock> m_CtrlBlocks;
    ER1Synth m_Synth;

    std::vector<juce::MidiMessage> m_QueuedMessages;
    juce::AudioBuffer<float> m_OversampleBuffer;
    std::unique_ptr<meta::ER1::Downsampler> m_Downsampler;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessor)
};
