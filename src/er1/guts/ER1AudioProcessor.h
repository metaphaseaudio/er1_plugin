/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <er1_dsp/Constants.h>
#include <er1_dsp/Envelope.h>
#include <meta/midi/MidiState.h>
#include <meta/dsp/Decimate.h>
#include "juce_synth/ER1Synth.h"
#include "juce_synth/ER1SoundPatch.h"
#include "juce_synth/ER1Voice.h"
#include "MidiManager.h"
#include "GlobalOptions.h"
#include "Patch.h"

//==============================================================================
/**
*/
class ER1AudioProcessor
    : public juce::AudioProcessor
    , public juce::ChangeBroadcaster
    , public JSONPatch
{
public:
    //==============================================================================
    ER1AudioProcessor();
    ~ER1AudioProcessor() override = default;
    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool canAddBus(bool isInput) const override;
    bool canRemoveBus(bool isInput) const override;

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
    GlobalOptions& getOptions() { return m_Opts; }

    ER1SoundPatch::Ptr getSound(int i) { return m_CtrlBlocks[i]; }
    void triggerVoice(int num);
    juce::ReferenceCountedArray<ER1SoundPatch>& getAllSounds() { return m_CtrlBlocks; }
    const ER1Synth& getSynth() const { return m_Synth; }

    juce::File getBankPresetFolder() const { return m_BankPresetFolder; };
    juce::File getSoundPresetFolder() const { return m_SoundPresetFolder; };

    void setBankPresetFolder(const juce::File& folder);
    void setSoundPresetFolder(const juce::File& folder);

    nlohmann::json toJsonInternal() const override;
    void fromJsonInternal(const nlohmann::json& json) override;

    void loadDefaultPatch();

private:
    static BusesProperties makeBusesProperties(int inBusses, int outBusses);

    void addMidiLearn(ER1SoundPatch* ctrls);
    void addAnalogVoice(int voiceNumber, bool canBeRingCarrier);
    void addAudioVoice(int voiceNumber, bool canBeRingCarrier);
    ER1Voice* addPCMVoice(std::string name, const char* data, int nData, float dataSampleRate);

    GlobalOptions m_Opts;
    using OverSample = juce::dsp::Oversampling<float>;
    meta::Decimate<float, meta::ER1::Downsampler::OverSample, 1> m_Decimate;
    std::unique_ptr<OverSample> m_Downsampler;

    MidiManager m_MidiManager;

    juce::ReferenceCountedArray<ER1SoundPatch> m_CtrlBlocks;
    ER1Synth m_Synth;
    juce::File m_BankPresetFolder, m_SoundPresetFolder;

    juce::AudioBuffer<float> m_OversampleBuffer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1AudioProcessor)
};
