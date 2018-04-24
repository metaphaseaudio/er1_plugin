#include <meta/audio/SingletonSampleRate.h>
#include "ER1AudioProcessor.h"
#include "../gooey/ER1AudioProcessorEditor.h"

using namespace juce;

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
{}

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

int ER1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int ER1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void ER1AudioProcessor::setCurrentProgram(int index)
{
}

const String ER1AudioProcessor::getProgramName(int index)
{
    return {};
}

void ER1AudioProcessor::changeProgramName(int index, const String &newName)
{
}

//==============================================================================
void ER1AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	for (int i = ER1_VOICE_COUNT; --i >= 0;)
	{
		m_Voices[i].oscillator.params.waveType = meta::ER1::Oscillator::WaveType::SINE;
		m_Voices[i].amplifier.envelope.amp = 1.0f;
		m_Voices[i].amplifier.envelope.speed = 1.0f;
		m_Voices[i].pitchModulator.amp = 200.0f;
		m_Voices[i].pitchModulator.speed = 1.5f;
		m_Voices[i].oscPitch = 20;
		m_Voices[i].updateParams();
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
			m_Voices[0].reset(); 
			m_Voices[0].start();
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
