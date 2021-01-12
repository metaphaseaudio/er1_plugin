#include <meta/audio/SingletonSampleRate.h>
#include <meta/util/math.h>
#include "ER1AudioProcessor.h"
#include "../gooey/ER1AudioProcessorEditor.h"

using namespace juce;
static juce::StringArray OscNames =
        {
            "Sine"
            , "Triangle"
        };
static juce::StringArray ModulationNames =
        {
            "Saw"
            , "Square"
            , "Triangle"
            , "SAH"
            , "Noise"
            , "Decay"
        };
//==============================================================================
ER1AudioProcessor::ER1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    m_Synth.setCurrentPlaybackSampleRate(48000);
    for (int i = 0; i < ER1_VOICE_COUNT; i++)
    {
        // Create params
        auto voiceIDStr = "voice_" + juce::String(i);

        auto* oscType = new juce::AudioParameterChoice(voiceIDStr + "_osc_type", voiceIDStr + " Oscillator Type", OscNames, 0);
        auto* modType = new juce::AudioParameterChoice(voiceIDStr + "_mod_type", voiceIDStr + " Modulation Type", ModulationNames, 5);
        auto* pitch = new juce::AudioParameterFloat(voiceIDStr + "_pitch", voiceIDStr + " Oscillator Freq", 30.0f, 8750.0f, 250.0f);
        auto* modSpeed = new juce::AudioParameterFloat(voiceIDStr + "_mod_speed", voiceIDStr + " Modulation Speed", 0.0f, 1.0f, 0.1f);
        auto* modDepth = new juce::AudioParameterFloat(voiceIDStr + "_mod_depth", voiceIDStr + " Modulation Depth", -11000.0f, 11000.0f, 0.0f);

        auto* decay = new juce::AudioParameterFloat(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.01f, 1.0f, 0.1f);
        auto* level = new juce::AudioParameterFloat(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 0.6f);
        auto* pan = new juce::AudioParameterFloat(voiceIDStr + "_pan", voiceIDStr + " Pan", -1.0f, 1.0f, 0);
        auto* lowBoost = new juce::AudioParameterFloat(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", 0.0f, 1.0f, 0.0f);

        // Add params to processor
        addParameter(oscType);
        addParameter(pitch);
        addParameter(modType);
        addParameter(modSpeed);
        addParameter(modDepth);

        addParameter(level);
        addParameter(pan);
        addParameter(decay);
        addParameter(lowBoost);

        // Add Sound
        OscParams osc = {oscType, modType, pitch, modSpeed, modDepth};
        AmpParams amp = {decay, level, pan, lowBoost};

        m_Sounds.add(new ER1Sound(osc, amp, i, 0));
        auto sound = m_Sounds.getLast();
        m_Synth.addSound(sound);


    }
}

ER1AudioProcessor::~ER1AudioProcessor() {}

//==============================================================================
const String ER1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ER1AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ER1AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ER1AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ER1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ER1AudioProcessor::getNumPrograms() { return 1; }

int ER1AudioProcessor::getCurrentProgram() { return 0; }

void ER1AudioProcessor::setCurrentProgram(int index) {}

const String ER1AudioProcessor::getProgramName(int index) { return {}; }

void ER1AudioProcessor::changeProgramName(int index, const String &newName) {}

//==============================================================================
void ER1AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    m_Synth.setCurrentPlaybackSampleRate(sampleRate);
//	for (int i = ER1_VOICE_COUNT; --i >= 0;)
//	{
//		m_Voices[i].oscillator.waveType = meta::ER1::Oscillator::WaveType::SINE;
//        m_Voices[i].setPitch(250);
//        m_Voices[i].level = 1.0f;
//        m_Voices[i].setModulationType(meta::ER1::Voice::ModType::DECAY);
//        m_Voices[i].setModulationSpeed(1.0f);
//        m_Voices[i].setModulationDepth(100.0f);
//        m_Voices[i].envelope.setSpeed(0.1f);
//		m_Voices[i].reset();
//	}
}

void ER1AudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ER1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void ER1AudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
    ScopedNoDenormals noDenormals;

    // Prep Params
//    for (int i = ER1_VOICE_COUNT; --i >= 0;)
//    {
//        auto& voice = m_Voices[i];
//
//		voice.setPitch(m_VoicePitch[i]->get());
//		voice.envelope.setSpeed(m_VoiceDecay[i]->get());
//
//        voice.oscillator.waveType = static_cast<meta::ER1::Oscillator::WaveType>(m_VoiceWaveType[i]->getIndex() + 1);
//        voice.oscillator.setFrequency(m_VoicePitch[i]->get());
//
//		voice.setModulationType(static_cast<meta::ER1::Voice::ModType>(m_VoiceModType[i]->getIndex()));
//        voice.setModulationDepth(m_VoiceModDepth[i]->get());
//        voice.setModulationSpeed
//            (meta::Interpolate<float>::parabolic(0.1f, 11000.0f, m_VoiceModSpeed[i]->get(), 5.0f));
//    }

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamplesLeft = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        { buffer.clear(i, 0, buffer.getNumSamples()); }

    m_Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

//    juce::MidiBuffer::Iterator itr(midiMessages);
//    itr.setNextSamplePosition(0);

//    juce::MidiMessage m;
//    int midiEventSample;
//    auto samplesRendered = 0;

//    while (itr.getNextEvent(m, midiEventSample))
//    {
//        const auto samplesToNextMessage = midiEventSample - samplesRendered;
//
//        for (int i = 0; i < ER1_VOICE_COUNT; i++)
//        {
//            m_Voices[i].processBlock(buffer.getArrayOfWritePointers()
//                                    , totalNumOutputChannels
//                                    , samplesToNextMessage
//                                    , samplesRendered);
//        }
//
//        if (m.isNoteOn())
//		{
//			const int note = m.getNoteNumber() % ER1_VOICE_COUNT;
//			m_Voices[note].level = m.getFloatVelocity();
//			m_Voices[note].reset();
//			m_Voices[note].start();
//		}
//
//		samplesRendered += samplesToNextMessage;
//    }
//
//    // generate the remaining audio
//    for (int i = 0; i < ER1_VOICE_COUNT; i++)
//    {
//        m_Voices[i].processBlock(buffer.getArrayOfWritePointers()
//                , totalNumOutputChannels
//                , buffer.getNumSamples() - samplesRendered
//                , samplesRendered);
//    }
}

//==============================================================================
bool ER1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *ER1AudioProcessor::createEditor()
{
    return new ER1AudioProcessorEditor(*this);
}

//==============================================================================
void ER1AudioProcessor::getStateInformation(MemoryBlock &destData)
{}

void ER1AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
    { return new ER1AudioProcessor(); }
