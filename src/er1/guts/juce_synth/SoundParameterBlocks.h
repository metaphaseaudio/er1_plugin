//
// Created by Matt on 12/29/2020.
//

#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <nlohmann/json.hpp>
#include <er1_dsp/Constants.h>
#include <meta/midi/MidiLearnable.h>

using json = nlohmann::json;


struct ConfigParams
{
    std::string name = "New Sound";
    std::atomic<unsigned int> note = 1;
    std::atomic<unsigned int> chan = 1;
    std::atomic<unsigned int> bus = 0;

    json asJSON() const
    {
        return json({
            {"name", name},
            {"note", note.load()},
            {"chan", chan.load()},
            {"bus", bus.load()}
        });
    }

    void fromJSON(json j)
    {
        name = j.value("name", "New Sound");
        note = j.value("note", 1);
        chan = j.value("chan", 1);
        bus = std::min(meta::ER1::NumOutBuses, std::max(0, j.value("bus", 0)));
    }
};

struct OscParams
{
    juce::AudioParameterChoice* oscType;
    juce::AudioParameterChoice* modType;
    meta::MidiLearnableAudioParameterFloat* pitch;
    meta::MidiLearnableAudioParameterFloat* modSpeed;
    meta::MidiLearnableAudioParameterFloat* modDepth;
    juce::AudioParameterBool* enableRing;

    json asJSON() const
    {
        json rv = {};
        if (oscType != nullptr) { rv["osc_type"] = oscType->getIndex(); }
        if (modType != nullptr) { rv["mod_type"] = modType->getIndex(); }
        if (pitch != nullptr) { rv["pitch"] = pitch->get(); }
        if (modSpeed != nullptr) { rv["mod_speed"] = modSpeed->get(); }
        if (modDepth != nullptr) { rv["mod_depth"] = modDepth->get(); }
        if (enableRing != nullptr) { rv["enable_ring"] = enableRing->get(); }
        return rv;
    };

    void fromJSON(json j)
    {
        if (j.is_null())
            { return; }

        if (oscType != nullptr) { *oscType = j.value("osc_type", modType->getIndex()); }
        if (modType != nullptr) { *modType = j.value("mod_type", modType->getIndex()); }
        if (pitch != nullptr) { *pitch = j.value("pitch", pitch->get()); }
        if (modSpeed != nullptr) { *modSpeed = j.value("mod_speed", modSpeed->get()); }
        if (modDepth != nullptr) { *modDepth = j.value("mod_depth", modDepth->get()); }
        if (enableRing != nullptr) { *enableRing = j.value("enable_ring", enableRing->get()); }
    }
};

struct AmpParams
{
    meta::MidiLearnableAudioParameterFloat* decay;
    meta::MidiLearnableAudioParameterFloat* level;
    meta::MidiLearnableAudioParameterFloat* pan;
    meta::MidiLearnableAudioParameterFloat* lowBoost;

    json asJSON() const
    {
        return json({
            {"decay", decay->get()},
            {"level", level->get()},
            {"pan", pan->get()},
            {"lowBoost", lowBoost->get()}
        });
    }

    void fromJSON(json j)
    {
        *decay = j.value("decay", decay->get());
        *level = j.value("level", level->get());
        *pan = j.value("pan", pan->get());
        *lowBoost = j.value("lowBoost", lowBoost->get());
    }
};

struct DelayParams
{
    meta::MidiLearnableAudioParameterFloat* time;
    meta::MidiLearnableAudioParameterFloat* depth;
    juce::AudioParameterBool* sync;

    json asJSON() const
    {
        return json({
            {"time", time->get()},
            {"depth", depth->get()},
            {"sync", sync->get()}
        });
    }

    void fromJSON(json j)
    {
        *time = j.value("time", time->get());
        *depth = j.value("depth", depth->get());
        *sync = j.value("sync", sync->get());
    }
};
