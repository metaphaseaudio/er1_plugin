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
    for (int i = 0; i < ER1_VOICE_COUNT; i++)
    {
        auto voiceIDStr = "Voice_" + juce::String(i);
        //=========== Oscillator =============
        auto oscTypeIDStr = voiceIDStr + "_osc_type";
        auto oscTypeName = voiceIDStr + " Oscillator Type";
        m_VoiceWaveType.emplace_back
                (new AudioParameterChoice(oscTypeIDStr, oscTypeName, OscNames, 0));
        addParameter(m_VoiceWaveType.at(i));

        auto oscPitchIDStr = voiceIDStr + "_osc_pitch";
        auto oscPitchName = voiceIDStr + "Oscillator Freq";
        m_VoicePitch.emplace_back
                (new AudioParameterFloat(oscPitchIDStr, oscPitchName, 30.0f, 8750.0f, 250.0f));
        addParameter(m_VoicePitch.at(i));

        //=========== Modulation =============
        auto modTypeIDStr = voiceIDStr + "_mod_type";
        auto modTypeName = voiceIDStr + " Modulation Type";
        m_VoiceModType.emplace_back
                (new AudioParameterChoice(modTypeIDStr, modTypeName, ModulationNames, 5));
        addParameter(m_VoiceModType.at(i));

        auto modDepthIDStr = voiceIDStr + "_mod_depth";
        auto modDepthName = voiceIDStr + " Modulation Depth";
        m_VoiceModDepth.emplace_back
                (new AudioParameterFloat(modDepthIDStr, modDepthName, -11000.0f, 11000.0f, 0.0f));
        addParameter(m_VoiceModDepth.at(i));

        auto modSpeedIDStr = voiceIDStr + "_mod_speed";
        auto modSpeedName = voiceIDStr + " Modulation Speed";
        m_VoiceModSpeed.emplace_back
                (new AudioParameterFloat(modSpeedIDStr, modSpeedName, 0.0f, 1.0f, 0.1f));
        addParameter(m_VoiceModSpeed.at(i));

        //============ Amplifier ==============
        auto decayIDStr = voiceIDStr + "_decay";
        auto decayName = voiceIDStr + " Decay";
        m_VoiceDecay.emplace_back
                (new AudioParameterFloat(decayIDStr, decayName, 0.01f, 1.0f, 0.1f));
        addParameter(m_VoiceDecay.at(i));
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
	for (int i = ER1_VOICE_COUNT; --i >= 0;)
	{
		m_Voices[i].oscillator.waveType = meta::ER1::Oscillator::WaveType::SINE;
        m_Voices[i].setPitch(250);
        m_Voices[i].level = 1.0f;
        m_Voices[i].setModulationType(meta::ER1::Voice::ModType::DECAY);
        m_Voices[i].setModulationSpeed(1.0f);
        m_Voices[i].setModulationDepth(100.0f);
        m_Voices[i].envelope.setSpeed(0.1f);
		m_Voices[i].reset();
	}
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
    for (int i = ER1_VOICE_COUNT; --i >= 0;)
    {
        auto& voice = m_Voices[i];

		voice.setPitch(m_VoicePitch[i]->get());
		voice.envelope.setSpeed(m_VoiceDecay[i]->get());

        voice.oscillator.waveType = static_cast<meta::ER1::Oscillator::WaveType>(m_VoiceWaveType[i]->getIndex() + 1);
        voice.oscillator.setFrequency(m_VoicePitch[i]->get());

		voice.setModulationType(static_cast<meta::ER1::Voice::ModType>(m_VoiceModType[i]->getIndex()));
        voice.setModulationDepth(m_VoiceModDepth[i]->get());
        voice.setModulationSpeed
            (meta::Interpolate<float>::parabolic(0.1f, 11000.0f, m_VoiceModSpeed[i]->get(), 5.0f));
    }

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamplesLeft = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        { buffer.clear(i, 0, buffer.getNumSamples()); }

    juce::MidiBuffer::Iterator itr(midiMessages);
    itr.setNextSamplePosition(0);

    juce::MidiMessage m;
    int midiEventSample;
    auto samplesRendered = 0;

    while (itr.getNextEvent(m, midiEventSample))
    {
        const auto samplesToNextMessage = midiEventSample - samplesRendered;

        for (int i = 0; i < ER1_VOICE_COUNT; i++)
        {
            m_Voices[i].processBlock(buffer.getArrayOfWritePointers()
                                    , totalNumOutputChannels
                                    , samplesToNextMessage
                                    , samplesRendered);
        }

        if (m.isNoteOn()) 
		{
			const int note = m.getNoteNumber() % ER1_VOICE_COUNT;
			m_Voices[note].level = m.getFloatVelocity();
			m_Voices[note].reset(); 
			m_Voices[note].start();
		}

		samplesRendered += samplesToNextMessage;
    }

    // generate the remaining audio
    for (int i = 0; i < ER1_VOICE_COUNT; i++)
    {
        m_Voices[i].processBlock(buffer.getArrayOfWritePointers()
                , totalNumOutputChannels
                , buffer.getNumSamples() - samplesRendered
                , samplesRendered);
    }
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
