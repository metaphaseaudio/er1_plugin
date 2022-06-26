//
// Created by Matt on 12/29/2020.
//

#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <nlohmann/json.hpp>
#include <er1_dsp/Constants.h>
#include <meta/midi/MidiLearnable.h>
#include "../LearnableSerializeableParam.h"

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
    LearnableSerializeable<juce::AudioParameterFloat>* pitch;
    LearnableSerializeable<juce::AudioParameterFloat>* modSpeed;
    LearnableSerializeable<juce::AudioParameterFloat>* modDepth;
    juce::AudioParameterBool* enableRing;

    [[nodiscard]] json asJSON() const
    {
        json rv = {};
        if (oscType != nullptr) { rv["osc_type"] = oscType->getIndex(); }
        if (modType != nullptr) { rv["mod_type"] = modType->getIndex(); }
        if (pitch != nullptr) { rv["pitch"] = pitch->toJson(); }
        if (modSpeed != nullptr) { rv["mod_speed"] = modSpeed->toJson(); }
        if (modDepth != nullptr) { rv["mod_depth"] = modDepth->toJson(); }
        if (enableRing != nullptr) { rv["enable_ring"] = enableRing->get(); }
        return rv;
    };

    void fromJSON(json j)
    {
        if (j.is_null())
            { return; }

        if (oscType != nullptr) { *oscType = j.value("osc_type", modType->getIndex()); }
        if (modType != nullptr) { *modType = j.value("mod_type", modType->getIndex()); }
        if (pitch != nullptr) { pitch->fromJson(j["pitch"]); }
        if (modSpeed != nullptr) { modSpeed->fromJson(j["mod_speed"]); }
        if (modDepth != nullptr) { modDepth->fromJson(j["mod_depth"]); }
        if (enableRing != nullptr) { *enableRing = j.value("enable_ring", enableRing->get()); }
    }
};

struct AmpParams
{
    LearnableSerializeable<juce::AudioParameterFloat>* decay;
    LearnableSerializeable<juce::AudioParameterFloat>* level;
    LearnableSerializeable<juce::AudioParameterFloat>* pan;
    LearnableSerializeable<juce::AudioParameterFloat>* lowBoost;

    json asJSON() const
    {
        return json({
            {"decay", decay->toJson()},
            {"level", level->toJson()},
            {"pan", pan->toJson()},
            {"lowBoost", lowBoost->toJson()}
        });
    }

    void fromJSON(json j)
    {
        decay->fromJson(j["decay"]);
        level->fromJson(j["level"]);
        pan->fromJson(j["pan"]);
        lowBoost->fromJson(j["lowBoost"]);
    }
};

struct DelayParams
{
    LearnableSerializeable<juce::AudioParameterFloat>* time;
    LearnableSerializeable<juce::AudioParameterFloat>* depth;
    juce::AudioParameterBool* sync;

    json asJSON() const
    {
        return json({
            {"time", time->toJson()},
            {"depth", depth->toJson()},
            {"sync", sync->get()}
        });
    }

    void fromJSON(json j)
    {
        time->fromJson(j["time"]);
        depth->fromJson(j["depth"]);
        *sync = j.value("sync", sync->get());
    }
};
