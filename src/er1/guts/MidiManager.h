//
// Created by Mattb on 6/13/2022.
//

#pragma once

#include <map>
#include <meta/midi/MidiLearnable.h>
#include <nlohmann/json.hpp>
#include "juce_synth/ER1ControlBlock.h"


class MidiManager
    : public meta::MidiLearnBroadcaster::Listener
    , public juce::ChangeBroadcaster
{
public:
    using MidiCtrlNumber = int;

    bool isLearning() const { return m_CurrentlyLearning != nullptr; }
    void stopLearn();
    void startLearn(meta::MidiLearnBroadcaster* broadcaster) override;
    void unlearn(meta::MidiLearnBroadcaster* broadcaster) override;
    void addToLearnedList(meta::MidiLearnBroadcaster* broadcaster);
    void processBlock(juce::MidiBuffer& midi);

    void startListen() { m_IsListening = true; }
    void stopListen() { m_IsListening = false; }
    [[nodiscard]] bool isListening() const { return m_IsListening.load(); }
    void setActiveVoice(ER1ControlBlock* sound) { m_ActiveVoice = sound; }
    ER1ControlBlock* getActiveVoice() const { return m_ActiveVoice; }

    nlohmann::json getState() const;
    void setState(const nlohmann::json& newState);


private:
    std::vector<meta::MidiLearnBroadcaster*> m_LearnedList;
    std::atomic<meta::MidiLearnBroadcaster*> m_CurrentlyLearning;
    std::atomic<ER1ControlBlock*> m_ActiveVoice;
    std::atomic<bool> m_IsListening;
    std::map<MidiCtrlNumber, std::string> m_GlobalLearnMap;
    juce::MidiKeyboardState m_State;
};
