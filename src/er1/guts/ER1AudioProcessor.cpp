#include <meta/audio/SingletonSampleRate.h>
#include <meta/util/math.h>
#include "ER1AudioProcessor.h"
#include "../gooey/ER1AudioProcessorEditor.h"

using namespace juce;
static juce::StringArray OscNames =
        {
            "Sine"
            , "Triangle"
            , "Square"
            , "Saw"
            , "Inverse Saw"
        };

static juce::StringArray ModulationNames =
        {
            "Sine"
            , "Triangle"
            , "Square"
            , "Saw"
            , "Inverse Saw"
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
    m_Synth.setCurrentPlaybackSampleRate(44100);
    meta::SingletonSampleRate<float>::setValue(44100);
    for (int i = 0; i < ER1_SOUND_COUNT; i++)
    {
        // Create params
        auto voiceIDStr = "voice_" + juce::String(i);

        auto* oscType = new juce::AudioParameterChoice(voiceIDStr + "_osc_type", voiceIDStr + " Oscillator Type", OscNames, 0);
        auto* modType = new juce::AudioParameterChoice(voiceIDStr + "_mod_type", voiceIDStr + " Modulation Type", ModulationNames, 0);
        auto* pitch = new juce::AudioParameterFloat(voiceIDStr + "_pitch", voiceIDStr + " Oscillator Freq", 30.0f, 4000.0f, 250.0f);
        auto* modSpeed = new juce::AudioParameterFloat(voiceIDStr + "_mod_speed", voiceIDStr + " Modulation Speed", 0.0f, 500.0f, 0.5f);
        auto* modDepth = new juce::AudioParameterFloat(voiceIDStr + "_mod_depth", voiceIDStr + " Modulation Depth", -1100.0f, 1100.0f, 200.0f);

        auto* decay = new juce::AudioParameterFloat(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.01f, 1.0f, 0.1f);
        auto* level = new juce::AudioParameterFloat(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 1.0f);
        auto* pan = new juce::AudioParameterFloat(voiceIDStr + "_pan", voiceIDStr + " Pan", 0.0f, 1.0f, 0.5);
        auto* lowBoost = new juce::AudioParameterFloat(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", 0.0f, 1.0f, 0.0f);

        auto* time = new juce::AudioParameterFloat(voiceIDStr + "_time", voiceIDStr + " Pan", 0.0f, 1.0f, 0.5);
        auto* depth = new juce::AudioParameterFloat(voiceIDStr + "_depth", voiceIDStr + " Low Boost", 0.0f, 1.0f, 0.0f);

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

        addParameter(time);
        addParameter(depth);

        // Add Sound
        OscParams osc = {oscType, modType, pitch, modSpeed, modDepth};
        AmpParams amp = {decay, level, pan, lowBoost};
        DelayParams delay = {time, depth};

        m_Sounds.add(new ER1Sound(osc, amp, delay, 1, 1));
        auto sound = m_Sounds.getLast();
        m_Synth.addSound(sound);
    }

    for (auto i = 0; i < ER1_MAX_POLYPHONY; i++) { m_Synth.addVoice(new ER1Voice()); }
}


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

void ER1AudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    buffer.clear();
    m_Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
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
{
    MemoryOutputStream stream(destData, true);

    for (const auto sound : m_Sounds)
    {
        stream.writeString(sound->config.name);
        stream.writeInt(sound->config.note);
        stream.writeInt(sound->config.chan);
        stream.writeFloat(*sound->osc.pitch);
        stream.writeInt(*sound->osc.oscType);
        stream.writeInt(*sound->osc.modType);
        stream.writeFloat(*sound->osc.modSpeed);
        stream.writeFloat(*sound->osc.modDepth);

        stream.writeFloat(*sound->amp.decay);
        stream.writeFloat(*sound->amp.level);
        stream.writeFloat(*sound->amp.pan);
        stream.writeFloat(*sound->amp.lowBoost);

        stream.writeFloat(*sound->delay.time);
        stream.writeFloat(*sound->delay.depth);
    }
}


void ER1AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);

    for (const auto sound : m_Sounds)
    {
        sound->config.name = stream.readString().toStdString();
        sound->config.note = stream.readInt();
        sound->config.chan = stream.readInt();
        sound->osc.pitch->setValueNotifyingHost(stream.readFloat());
        sound->osc.oscType->setValueNotifyingHost(stream.readInt());
        sound->osc.modType->setValueNotifyingHost(stream.readInt());
        sound->osc.modSpeed->setValueNotifyingHost(stream.readFloat());
        sound->osc.modDepth->setValueNotifyingHost(stream.readFloat());

        sound->amp.decay->setValueNotifyingHost(stream.readFloat());
        sound->amp.level->setValueNotifyingHost(stream.readFloat());
        sound->amp.pan->setValueNotifyingHost(stream.readFloat());
        sound->amp.lowBoost->setValueNotifyingHost(stream.readFloat());

        sound->delay.time->setValueNotifyingHost(stream.readFloat());
        sound->delay.depth->setValueNotifyingHost(stream.readFloat());

    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
    { return new ER1AudioProcessor(); }
