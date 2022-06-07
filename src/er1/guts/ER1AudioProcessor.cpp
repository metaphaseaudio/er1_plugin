#include <meta/util/math.h>
#include <nlohmann/json.hpp>
#include "ER1AudioProcessor.h"
#include "../gooey/ER1AudioProcessorEditor.h"
#include "er1_dsp/sounds/AnalogSound.h"
#include "er1_dsp/sounds/AudioSound.h"
#include "er1_dsp/sounds/PCMSound.h"
#include "er1_dsp/ER1PCMSamples.h"

using namespace juce;
using json = nlohmann::json;

static juce::StringArray OscNames =
{
    "Sine"
    , "Triangle"
    , "Square"
    , "Saw"
    , "Inv Saw"
};

static juce::StringArray ModulationNames =
{
    "Sine"
    , "Triangle"
    , "Square"
    , "Saw"
    , "Inv Saw"
    , "SAH"
    , "Noise"
    , "Decay"
};


//==============================================================================
ER1AudioProcessor::ER1AudioProcessor()
    : AudioProcessor(
        BusesProperties().withInput("Input",  AudioChannelSet::stereo())
                         .withOutput("Output", AudioChannelSet::stereo()))
    , m_Downsampler(44100)
{
    for (int i = 0; i < ANALOG_SOUND_COUNT; i++) { addAnalogVoice(i, (1 + i) % 2 == 0); }
    for (int i = 0; i < AUDIO_SOUND_COUNT; i++) { addAudioVoice(i, i == 0); }

    auto ch = addPCMVoice("Closed Hat", ER1PCMSamples::closed_hat_wav, ER1PCMSamples::closed_hat_wavSize, 32000);
    auto oh = addPCMVoice("Open Hat", ER1PCMSamples::open_hat_wav, ER1PCMSamples::open_hat_wavSize, 32000);
    auto cr = addPCMVoice("Crash", ER1PCMSamples::crash_wav, ER1PCMSamples::crash_wavSize, 32000);
    auto cl = addPCMVoice("Clap", ER1PCMSamples::clap_wav, ER1PCMSamples::clap_wavSize, 32000);

    oh->addToChokeList(ch);
    ch->addToChokeList(oh);

    cr->addToChokeList(cl);
    cl->addToChokeList(cr);
}


//==============================================================================
const String ER1AudioProcessor::getName() const { return JucePlugin_Name; }

bool ER1AudioProcessor::acceptsMidi() const { return true; }
bool ER1AudioProcessor::producesMidi() const { return false; }
bool ER1AudioProcessor::isMidiEffect() const { return false; }

double ER1AudioProcessor::getTailLengthSeconds() const { return 0.0; }
int ER1AudioProcessor::getNumPrograms() { return 1; }
int ER1AudioProcessor::getCurrentProgram() { return 0; }
void ER1AudioProcessor::setCurrentProgram(int index) {}
const String ER1AudioProcessor::getProgramName(int index) { return {}; }
void ER1AudioProcessor::changeProgramName(int index, const String &newName) {}

//==============================================================================
void ER1AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    m_Downsampler.set_sample_rate(sampleRate);
    m_Synth.prepareToPlay(sampleRate, samplesPerBlock * meta::ER1::Downsampler::OverSample);
    m_OversampleBuffer.setSize(2, samplesPerBlock * meta::ER1::Downsampler::OverSample);
}

void ER1AudioProcessor::releaseResources() {}

bool ER1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& mainInLayout  = layouts.getChannelSet (true,  0);
    const auto& mainOutLayout = layouts.getChannelSet (false, 0);

    return (mainInLayout == mainOutLayout && (! mainInLayout.isDisabled()));
}

void ER1AudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    while (!m_QueuedMessages.empty())
    {
        midiMessages.addEvent(m_QueuedMessages.back(), 0);
        m_QueuedMessages.pop_back();
    }

    m_OversampleBuffer.clear();
    m_OversampleBuffer.copyFrom(0, 0, buffer, 0, 0, buffer.getNumSamples());
    m_OversampleBuffer.copyFrom(1, 0, buffer, 1, 0, buffer.getNumSamples());
    m_Synth.processBlock(m_OversampleBuffer, midiMessages, buffer.getNumSamples());
    m_Downsampler.downsampleBuffer(m_OversampleBuffer, buffer);
    midiMessages.clear();
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

    json j = {};
    j["analog"] = json::array();
    j["audio"] = json::array();
    j["pcm"] = json::array();

    for (auto i = 0; i < ANALOG_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["analog"].push_back(sound->asJSON());
    }

    for (auto i = ANALOG_SOUND_COUNT; i < ANALOG_SOUND_COUNT + AUDIO_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["audio"].push_back(sound->asJSON());
    }

    for (auto i = ANALOG_SOUND_COUNT + AUDIO_SOUND_COUNT; i < ER1_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["pcm"].push_back(sound->asJSON());
    }

    stream.writeString(j.dump(4));
}


void ER1AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);

    json j = json::parse(stream.readString().toStdString());

    for (int i = 0; i < ANALOG_SOUND_COUNT || i < j["analog"].size(); i++)
    {
        auto ctrls = m_CtrlBlocks[i];
        ctrls->fromJSON(j["analog"][i]);
    }

    for (int i = 0; i < AUDIO_SOUND_COUNT || i < j["audio"].size(); i++)
    {
        auto ctrls = m_CtrlBlocks[i + ANALOG_SOUND_COUNT];
        ctrls->fromJSON(j["analog"][i]);
    }

    for (int i = 0; i < SAMPLE_SOUND_COUNT || i < j["pcm"].size(); i++)
    {
        auto ctrls = m_CtrlBlocks[i + ANALOG_SOUND_COUNT + AUDIO_SOUND_COUNT];
        ctrls->fromJSON(j["analog"][i]);
    }
}

void ER1AudioProcessor::triggerVoice(int voice)
{
    const auto& chan = m_CtrlBlocks[voice]->config.chan;
    const auto& note = m_CtrlBlocks[voice]->config.note;
    m_QueuedMessages.push_back(juce::MidiMessage::noteOn(chan, note, 1.0f));
}

void ER1AudioProcessor::addAnalogVoice(int voiceNumber, bool canBeRingCarrier)
{
    // Create params
    auto voiceIDStr = "analog_voice_" + juce::String(voiceNumber);

    auto* oscType = new juce::AudioParameterChoice(voiceIDStr + "_osc_type", voiceIDStr + " Oscillator Type", OscNames, 0);
    auto* modType = new juce::AudioParameterChoice(voiceIDStr + "_mod_type", voiceIDStr + " Modulation Type", ModulationNames, 0);
    auto* pitch = new juce::AudioParameterFloat(voiceIDStr + "_pitch", voiceIDStr + " Oscillator Freq", 0.0f, 1.0f, 0.2f);
    auto* modSpeed = new juce::AudioParameterFloat(voiceIDStr + "_mod_speed", voiceIDStr + " Modulation Speed", 0.0f, 1.0f, 0.0f);
    auto* modDepth = new juce::AudioParameterFloat(voiceIDStr + "_mod_depth", voiceIDStr + " Modulation Depth", -1.0f, 1.0f, 0.0f);
    auto* ring = canBeRingCarrier ? new juce::AudioParameterBool(voiceIDStr + "_ring_mod", voiceIDStr + " Ring Mod", false) : nullptr;

    auto* decay = new juce::AudioParameterFloat(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.01f, 1.0f, 0.1f);
    auto* level = new juce::AudioParameterFloat(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 1.0f);
    auto* pan = new juce::AudioParameterFloat(voiceIDStr + "_pan", voiceIDStr + " Pan", 0.0f, 1.0f, 0.5);
    auto* lowBoost = new juce::AudioParameterFloat(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", 0.0f, 1.0f, 0.0f);

    auto* time = new juce::AudioParameterFloat(voiceIDStr + "_time", voiceIDStr + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new juce::AudioParameterFloat(voiceIDStr + "_depth", voiceIDStr + " Depth", 0.0f, 0.9f, 0.0f);
    auto* sync = new juce::AudioParameterBool(voiceIDStr + "_tempo_sync", voiceIDStr + " Tempo Sync", true);

    // Add params to processor
    addParameter(oscType);
    addParameter(pitch);
    addParameter(modType);
    addParameter(modSpeed);
    addParameter(modDepth);
    if (ring != nullptr) { addParameter(ring); }

    addParameter(level);
    addParameter(pan);
    addParameter(decay);
    addParameter(lowBoost);

    addParameter(time);
    addParameter(depth);
    addParameter(sync);

    // Add Sound
    OscParams osc = {oscType, modType, pitch, modSpeed, modDepth, ring};
    AmpParams amp = {decay, level, pan, lowBoost};
    DelayParams delay = {time, depth, sync};

    m_CtrlBlocks.add(new ER1ControlBlock(osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();
    sound->config.name = voiceIDStr.toStdString();
    sound->config.chan = 1;
    sound->config.note = m_CtrlBlocks.size();

    m_Synth.addVoice(new ER1Voice(sound, new meta::ER1::AnalogSound(getSampleRate())));
}

void ER1AudioProcessor::addAudioVoice(int voiceNumber, bool canBeRingCarrier)
{
    // Create params
    auto voiceIDStr = "audio_voice_" + juce::String(voiceNumber);

    auto* ring = canBeRingCarrier ? new juce::AudioParameterBool(voiceIDStr + "_ring_mod", voiceIDStr + " Ring Mod", false) : nullptr;

    auto* decay = new juce::AudioParameterFloat(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.01f, 1.0f, 0.1f);
    auto* level = new juce::AudioParameterFloat(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 1.0f);
    auto* pan = new juce::AudioParameterFloat(voiceIDStr + "_pan", voiceIDStr + " Pan", 0.0f, 1.0f, 0.5);
    auto* lowBoost = new juce::AudioParameterFloat(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", 0.0f, 1.0f, 0.0f);

    auto* time = new juce::AudioParameterFloat(voiceIDStr + "_time", voiceIDStr + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new juce::AudioParameterFloat(voiceIDStr + "_depth", voiceIDStr + " Depth", 0.0f, 0.9f, 0.0f);
    auto* sync = new juce::AudioParameterBool(voiceIDStr + "_tempo_sync", voiceIDStr + " Tempo Sync", true);

    // Add params to processor
    if (ring != nullptr) { addParameter(ring); }

    addParameter(level);
    addParameter(pan);
    addParameter(decay);
    addParameter(lowBoost);

    addParameter(time);
    addParameter(depth);
    addParameter(sync);

    // Add Sound
    OscParams osc = {nullptr, nullptr, nullptr, nullptr, nullptr, ring};
    AmpParams amp = {decay, level, pan, lowBoost};
    DelayParams delay = {time, depth, sync};

    m_CtrlBlocks.add(new ER1ControlBlock(osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();
    sound->config.name = voiceIDStr.toStdString();
    sound->config.chan = 1;
    sound->config.note = m_CtrlBlocks.size();

    m_Synth.addVoice(
        new ER1Voice(
            sound,
            new meta::ER1::AudioSound(
                getSampleRate(),
                voiceNumber == 0 ? meta::ER1::AudioSound::AudioChannel::LEFT : meta::ER1::AudioSound::AudioChannel::RIGHT
            )
        )
    );
}

ER1Voice* ER1AudioProcessor::addPCMVoice(std::string name, const char* data, const int nData, float dataSampleRate)
{
    // Create params
    auto* pitch = new juce::AudioParameterFloat(name + "_pitch", name + " Pitch", 0.5f, 2.0f, 1.0f);

    auto* decay = new juce::AudioParameterFloat(name + "_decay", name + " Decay", 0.01f, 1.0f, 0.1f);
    auto* level = new juce::AudioParameterFloat(name + "_level", name + " Level", 0.0f, 1.0f, 1.0f);
    auto* pan = new juce::AudioParameterFloat(name + "_pan", name + " Pan", 0.0f, 1.0f, 0.5);
    auto* lowBoost = new juce::AudioParameterFloat(name + "_low_boost", name + " Low Boost", 0.0f, 1.0f, 0.0f);

    auto* time = new juce::AudioParameterFloat(name + "_time", name + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new juce::AudioParameterFloat(name + "_depth", name + " Depth", 0.0f, 0.9f, 0.0f);
    auto* sync = new juce::AudioParameterBool(name + "_tempo_sync", name + " Tempo Sync", true);

    // Add params to processor
    addParameter(pitch);

    addParameter(level);
    addParameter(pan);
    addParameter(decay);
    addParameter(lowBoost);

    addParameter(time);
    addParameter(depth);
    addParameter(sync);

    // Add Sound
    OscParams osc = {nullptr, nullptr, pitch, nullptr, nullptr, nullptr};
    AmpParams amp = {decay, level, pan, lowBoost};
    DelayParams delay = {time, depth, sync};

    m_CtrlBlocks.add(new ER1ControlBlock(osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();
    sound->config.name = name;
    sound->config.chan = 1;
    sound->config.note = m_CtrlBlocks.size();

    return m_Synth.addVoice(
        new ER1Voice(
            sound,
            new meta::ER1::PCMSound(
                getSampleRate(),
                ER1PCMSamples::loadBinaryPCMData(data, nData), dataSampleRate
            )
        )
    );
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
    { return new ER1AudioProcessor(); }
