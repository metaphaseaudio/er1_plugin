#include <meta/util/math.h>
#include <meta/util/container_helpers/memory.h>
#include <nlohmann/json.hpp>
#include <memory>
#include "ER1AudioProcessor.h"
#include "../gooey/ER1AudioProcessorEditor.h"
#include "er1_dsp/sounds/AnalogSound.h"
#include "er1_dsp/sounds/AudioSound.h"
#include "er1_dsp/sounds/PCMSound.h"
#include "er1_dsp/ER1PCMSamples.h"
#include <meta/midi/MidiLearnable.h>
#include <juce_dsp/juce_dsp.h>


using namespace juce;
using json = nlohmann::json;
using FloatParam = LearnableSerializeable<juce::AudioParameterFloat>;

constexpr int kDefaultStartingNote = 60;

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


static juce::File getPatchDir(const std::string& dir)
{
    const auto defaultDir = juce::File(
#ifdef  JUCE_LINUX
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory)
                .getChildFile("metaphase")
                .getChildFile("er1_presets")
#elif JUCE_WINDOWS
            juce::WindowsRegistry::getValue(
            R"(HKEY_CURRENT_USER\SOFTWARE\Metaphase\ER1\PresetInstallPath)",
            juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName()
        )
#else
#endif
    );

    auto patchDir = defaultDir
            .getChildFile("metaphase")
            .getChildFile("er1")
            .getChildFile(dir);

    if (!patchDir.exists())
        { patchDir.createDirectory(); }
    return patchDir;
}


//==============================================================================
ER1AudioProcessor::ER1AudioProcessor()
    : AudioProcessor(makeBusesProperties(1, meta::ER1::NumOutBuses))
    , m_BankPresetFolder(getPatchDir("banks"))
    , m_SoundPresetFolder(getPatchDir("sounds"))
{
    // The first voice gets skipped as a ring carrier, but every other voice after that can be.
    for (int i = 0; i < meta::ER1::ANALOG_SOUND_COUNT; i++) { addAnalogVoice(i, i > 0 && i % 2 == 0); }
    for (int i = 0; i < meta::ER1::AUDIO_SOUND_COUNT; i++) { addAudioVoice(i, i == 0); }

    auto ch = addPCMVoice("Closed Hat", ER1PCMSamples::closed_hat_wav, ER1PCMSamples::closed_hat_wavSize, 32000);
    auto oh = addPCMVoice("Open Hat", ER1PCMSamples::open_hat_wav, ER1PCMSamples::open_hat_wavSize, 32000);
    auto cr = addPCMVoice("Crash", ER1PCMSamples::crash_wav, ER1PCMSamples::crash_wavSize, 32000);
    auto cl = addPCMVoice("Clap", ER1PCMSamples::clap_wav, ER1PCMSamples::clap_wavSize, 32000);

    oh->addToChokeList(ch);
    ch->addToChokeList(oh);

    cr->addToChokeList(cl);
    cl->addToChokeList(cr);

    loadDefaultPatch();
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
    const auto oversampleRate = sampleRate * meta::ER1::Downsampler::OverSample;
    const auto oversampleSize = samplesPerBlock * meta::ER1::Downsampler::OverSample;
    const auto nChans = getTotalNumOutputChannels();
    m_Downsampler = std::make_unique<OverSample>(nChans, meta::ER1::TWO_N_OVERSAMPLE, OverSample::FilterType::filterHalfBandPolyphaseIIR);
    m_Downsampler->initProcessing(samplesPerBlock);
    m_Synth.prepareToPlay(oversampleRate, nChans / 2, oversampleSize);
}

void ER1AudioProcessor::releaseResources() {}

bool ER1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layout) const
{
    for (const auto& bus : layout.outputBuses)
    {
        if (bus.isDisabled()) { continue; }
        if (bus != AudioChannelSet::stereo())
            return false;
    }

    return layout.inputBuses.size() == 1
        && layout.inputBuses[0] == AudioChannelSet::stereo()
        && layout.outputBuses.size() >= 1;
}

void ER1AudioProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    m_MidiManager.processBlock(midiMessages);

    // Get the BPM info
    juce::AudioPlayHead::CurrentPositionInfo positionInfo;
    auto ph = playHead.load();
    if (ph != nullptr)
        playHead.load()->getCurrentPosition(positionInfo);

    auto block = m_Downsampler->processSamplesUp(juce::dsp::AudioBlock<float>(buffer));
    m_Synth.processBlock(block, midiMessages, positionInfo.bpm);

    if (!m_Opts.enableAntialiasing)
    {
        auto outBlock = juce::dsp::AudioBlock<float>(buffer);
        m_Downsampler->processSamplesDown(outBlock);
    }
    else
    {
        for (int c = block.getNumChannels(); --c >= 0;)
            { m_Decimate(block.getChannelPointer(c), buffer.getWritePointer(c), block.getNumSamples()); }
    }

    midiMessages.clear();
}

//==============================================================================
bool ER1AudioProcessor::hasEditor() const { return true; }
AudioProcessorEditor *ER1AudioProcessor::createEditor() { return new ER1AudioProcessorEditor(*this, m_WidgetManager); }

//==============================================================================
void ER1AudioProcessor::getStateInformation(MemoryBlock &destData)
{
    MemoryOutputStream stream(destData, true);

    auto j = toJson();
    j["bank_dir"] = m_BankPresetFolder.getFullPathName().toStdString();
    j["sound_dir"] = m_SoundPresetFolder.getFullPathName().toStdString();
    stream.writeString(j.dump(4));
}


void ER1AudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);

    try
    {
        json j = json::parse(stream.readString().toStdString());

        fromJson(j);
        setBankPresetFolder(juce::File(j.value("bank_dir", getPatchDir("banks").getFullPathName().toStdString())));
        setSoundPresetFolder(juce::File(j.value("sound_dir", getPatchDir("sounds").getFullPathName().toStdString())));
    }
    catch (json::exception& err)
    {
        std::cerr << "Error loading ER1 State:" << err.what() << std::endl;
    }
}

void ER1AudioProcessor::triggerVoice(int voice)
{
    m_Synth.triggerVoice(voice);
}

void ER1AudioProcessor::addAnalogVoice(int voiceNumber, bool canBeRingCarrier)
{
    // Create params
    auto voiceIDStr = "analog_voice_" + juce::String(voiceNumber);

    auto* oscType = new juce::AudioParameterChoice(voiceIDStr + "_osc_type", voiceIDStr + " Oscillator Type", OscNames, 0);
    auto* modType = new juce::AudioParameterChoice(voiceIDStr + "_mod_type", voiceIDStr + " Modulation Type", ModulationNames, 0);

    auto* pitch = new FloatParam(voiceIDStr + "_pitch", voiceIDStr + " Oscillator Freq", 0.0f, 1.0f, 0.2f);
    auto* modSpeed = new FloatParam(voiceIDStr + "_mod_speed", voiceIDStr + " Modulation Speed", 0.0f, 1.0f, 0.0f);
    auto* modDepth = new FloatParam(voiceIDStr + "_mod_depth", voiceIDStr + " Modulation Depth", -1.0f, 1.0f, 0.0f);
    auto* ring = canBeRingCarrier ? new juce::AudioParameterBool(voiceIDStr + "_ring_mod", voiceIDStr + " Ring Mod", false) : nullptr;

    auto* decay = new FloatParam(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.0f, 1.0f, 0.5f);
    auto* level = new FloatParam(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 0.5f);
    auto* pan = new FloatParam(voiceIDStr + "_pan", voiceIDStr + " Pan", -1.0f, 1.0f, 0.0f);
    auto* lowBoost = new FloatParam(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", -1.0f, 1.0f, 0.0f);

    auto* time = new FloatParam(voiceIDStr + "_time", voiceIDStr + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new FloatParam(voiceIDStr + "_depth", voiceIDStr + " Depth", 0.0f, 0.9f, 0.0f);
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

    m_CtrlBlocks.add(new ER1SoundPatch(voiceIDStr.toStdString(), osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();

    m_SoundSlotConfigs.emplace_back(meta::make_unique_struct<ConfigParams>(kDefaultStartingNote + m_SoundSlotConfigs.size(), 1, 0, false, false, false));
    sound->config = m_SoundSlotConfigs.back().get();

    addMidiLearn(sound);
    m_Synth.addVoice(new ER1Voice(sound, new meta::ER1::AnalogSound(getSampleRate())));
}

void ER1AudioProcessor::addAudioVoice(int voiceNumber, bool canBeRingCarrier)
{
    // Create params
    auto voiceIDStr = "audio_voice_" + juce::String(voiceNumber);

    auto* ring = canBeRingCarrier ? new juce::AudioParameterBool(voiceIDStr + "_ring_mod", voiceIDStr + " Ring Mod", false) : nullptr;

    auto* decay = new FloatParam(voiceIDStr + "_decay", voiceIDStr + " Decay", 0.0f, 1.0f, 0.5f);
    auto* level = new FloatParam(voiceIDStr + "_level", voiceIDStr + " Level", 0.0f, 1.0f, 0.5f);
    auto* pan = new FloatParam(voiceIDStr + "_pan", voiceIDStr + " Pan", -1.0f, 1.0f, 0.0f);
    auto* lowBoost = new FloatParam(voiceIDStr + "_low_boost", voiceIDStr + " Low Boost", -1.0f, 1.0f, 0.0f);

    auto* time = new FloatParam(voiceIDStr + "_time", voiceIDStr + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new FloatParam(voiceIDStr + "_depth", voiceIDStr + " Depth", 0.0f, 0.9f, 0.0f);
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

    m_CtrlBlocks.add(new ER1SoundPatch(voiceIDStr.toStdString(), osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();

    m_SoundSlotConfigs.emplace_back(meta::make_unique_struct<ConfigParams>(kDefaultStartingNote + m_SoundSlotConfigs.size(), 1, 0, false, false, false));
    sound->config = m_SoundSlotConfigs.back().get();

    addMidiLearn(sound);
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

ER1Voice* ER1AudioProcessor::addPCMVoice(std::string name, const char* data, int nData, float dataSampleRate)
{
    // Create params
    auto* pitch = new FloatParam(name + "_pitch", name + " Pitch", 0.25f, 3.0f, 1.0f);

    auto* decay = new FloatParam(name + "_decay", name + " Decay", 0.0f, 1.0f, 0.75f);
    auto* level = new FloatParam(name + "_level", name + " Level", 0.0f, 1.0f, 0.5f);
    auto* pan = new FloatParam(name + "_pan", name + " Pan", -1.0f, 1.0f, 0.0f);
    auto* lowBoost = new FloatParam(name + "_low_boost", name + " Low Boost", -1.0f, 1.0f, 0.0f);

    auto* time = new FloatParam(name + "_time", name + " Time", 0.0f, 1.0f, 0.5f);
    auto* depth = new FloatParam(name + "_depth", name + " Depth", 0.0f, 0.9f, 0.0f);
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

    m_CtrlBlocks.add(new ER1SoundPatch(name, osc, amp, delay, 1, 1));
    auto sound = m_CtrlBlocks.getLast();

    m_SoundSlotConfigs.emplace_back(meta::make_unique_struct<ConfigParams>(kDefaultStartingNote + m_SoundSlotConfigs.size(), 1, 0, false, false, false));
    sound->config = m_SoundSlotConfigs.back().get();

    addMidiLearn(sound);
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

AudioProcessor::BusesProperties ER1AudioProcessor::makeBusesProperties(int inBusses, int outBusses)
{
    auto rv = AudioProcessor::BusesProperties();
    for (int i = 0; i < inBusses; i++)
        { rv = rv.withInput(juce::String("Input ") + juce::String(i), juce::AudioChannelSet::stereo(), i == 0); }

    for (int i = 0; i < outBusses; i++)
        { rv = rv.withOutput(juce::String("Output ") + juce::String(i), juce::AudioChannelSet::stereo(), true); }

    return rv;
}

void ER1AudioProcessor::addMidiLearn(ER1SoundPatch* ctrls)
{
    if (ctrls->osc.pitch != nullptr) { ctrls->osc.pitch->addMidiLearnListener(&m_MidiManager); }
    if (ctrls->osc.modSpeed != nullptr) { ctrls->osc.modSpeed->addMidiLearnListener(&m_MidiManager); }
    if (ctrls->osc.modDepth != nullptr) { ctrls->osc.modDepth->addMidiLearnListener(&m_MidiManager); }

    ctrls->amp.decay->addMidiLearnListener(&m_MidiManager);
    ctrls->amp.level->addMidiLearnListener(&m_MidiManager);
    ctrls->amp.pan->addMidiLearnListener(&m_MidiManager);
    ctrls->amp.lowBoost->addMidiLearnListener(&m_MidiManager);

    ctrls->delay.depth->addMidiLearnListener(&m_MidiManager);
    ctrls->delay.time->addMidiLearnListener(&m_MidiManager);
}

nlohmann::json ER1AudioProcessor::toJsonInternal() const
{
    json j = {
        {"midi_management", m_MidiManager.getState()},
        {"options", m_Opts.toJson()}
    };

    j["analog"] = json::array();
    j["audio"] = json::array();
    j["pcm"] = json::array();
    j["btn_config"] = json::array();

    for (auto i = 0; i < meta::ER1::ANALOG_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["analog"].push_back(sound->toJson());
    }

    for (auto i = meta::ER1::ANALOG_SOUND_COUNT; i < meta::ER1::ANALOG_SOUND_COUNT + meta::ER1::AUDIO_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["audio"].push_back(sound->toJson());
    }

    for (auto i = meta::ER1::ANALOG_SOUND_COUNT + meta::ER1::AUDIO_SOUND_COUNT; i < meta::ER1::ER1_SOUND_COUNT; i++)
    {
        const auto& sound = m_CtrlBlocks[i];
        j["pcm"].push_back(sound->toJson());
    }

    for (auto& cfg : m_SoundSlotConfigs)
    {
        j["btn_config"].push_back(cfg->toJson());
    }

    return j;
}

void ER1AudioProcessor::fromJsonInternal(const json& j)
{
    try
    {
        for (int i = 0; i < meta::ER1::ER1_SOUND_COUNT && i < j.at("btn_config").size(); i++)
        {
            // This propagates automatically to each of the sounds' control blocks.
            m_SoundSlotConfigs[i]->fromJson(j["btn_config"][i]);
        }

        for (int i = 0; i < meta::ER1::ANALOG_SOUND_COUNT && i < j.at("analog").size(); i++)
        {
            auto ctrls = m_CtrlBlocks[i];
            ctrls->fromJson(j["analog"][i]);
        }

        for (int i = 0; i < meta::ER1::AUDIO_SOUND_COUNT && i < j.at("audio").size(); i++)
        {
            auto ctrls = m_CtrlBlocks[i + meta::ER1::ANALOG_SOUND_COUNT];
            ctrls->fromJson(j["audio"][i]);
        }

        for (int i = 0; i < meta::ER1::SAMPLE_SOUND_COUNT && i < j.at("pcm").size(); i++)
        {
            auto ctrls = m_CtrlBlocks[i + meta::ER1::ANALOG_SOUND_COUNT + meta::ER1::AUDIO_SOUND_COUNT];
            ctrls->fromJson(j["pcm"][i]);
        }

        m_Opts.fromJson(j.at("options"));
    }
    catch (std::exception& err)
    {
        std::cout << "Error loading ER1 State:" << err.what() << std::endl;
    }

    m_MidiManager.clearAllLearnedParams();

    for (auto& param : getParameters())
    {
        auto learnable = dynamic_cast<meta::MidiLearnBroadcaster*>(param);
        if (learnable != nullptr && learnable->isLearned())
        { m_MidiManager.addToLearnedList(learnable); }
    }
}

bool ER1AudioProcessor::canAddBus(bool isInput) const
{
    if (isInput && getBusCount(true) < 1) { return true; }
    return getBusCount(false) < meta::ER1::NumOutBuses;
}

bool ER1AudioProcessor::canRemoveBus(bool isInput) const
{
    if (isInput) { return false; }
    return getBusCount(false) > 1;
}

void ER1AudioProcessor::setBankPresetFolder(const File& folder)
{
    m_BankPresetFolder = folder;
    sendChangeMessage();
}

void ER1AudioProcessor::setSoundPresetFolder(const File& folder)
{
    m_SoundPresetFolder = folder;
    sendChangeMessage();
}

void ER1AudioProcessor::loadDefaultPatch()
{
    // If we're just dealing with a default, we might as well try to load a patch from the patch directory
    auto itr = juce::RangedDirectoryIterator(getPatchDir("banks"), false);
    for (auto& entry : itr)
    {
        auto file = entry.getFile();
        loadPatch(file);
        sendChangeMessage();
        break;
    }
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor *JUCE_CALLTYPE createPluginFilter()
    { return new ER1AudioProcessor(); }
