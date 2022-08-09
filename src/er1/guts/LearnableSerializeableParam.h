//
// Created by Matt on 6/18/2022.
//
#pragma once
#include <meta/midi/MidiLearnable.h>
#include <nlohmann/json.hpp>


class Serializeable
{
public:
    virtual void fromJson(const nlohmann::json& json) = 0;
    [[nodiscard]] virtual nlohmann::json toJson() const = 0;
};

template <typename ParamType>
class LearnableSerializeable
    : public ParamType
    , public Serializeable
    , public meta::MidiLearnBroadcaster
{
    static_assert(std::derived_from<ParamType, juce::RangedAudioParameter>, "ParamType must be derived from a juce::RangedAudioParameter");
    static constexpr auto key_value = "value";
    static constexpr auto key_midi_ctrl_num = "midi_ctrl_num";
    static constexpr auto key_midi_chan = "midi_chan";

public:
    using ParamType::ParamType;

    void handleMidiMessage(const juce::MidiMessage& msg) override
    {
        if (m_Ctrl.getControllerNumber() == msg.getControllerNumber() && m_Ctrl.getChannel() == msg.getChannel())
            { static_cast<juce::RangedAudioParameter*>(this)->setValueNotifyingHost(float(msg.getControllerValue()) / 127.0f); }
    };

    [[nodiscard]] nlohmann::json toJson() const override
    {
        nlohmann::json rv = {
            {key_value, static_cast<const juce::RangedAudioParameter*>(this)->getValue()}
        };

        if (isLearned())
        {
            rv[key_midi_chan] = m_Ctrl.getChannel();
            rv[key_midi_ctrl_num] = m_Ctrl.getControllerNumber();
        }

        return rv;
    }

    void fromJson(const nlohmann::json& json) override
    {
        const auto value = json[key_value];
        static_cast<juce::RangedAudioParameter*>(this)->setValueNotifyingHost(value);

        if (json.contains(key_midi_ctrl_num) && json.contains(key_midi_chan))
            { setLearnedControl(juce::MidiMessage::controllerEvent(json[key_midi_chan], json[key_midi_ctrl_num], 0.0f)); }
    }
};
