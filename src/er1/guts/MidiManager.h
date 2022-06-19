//
// Created by Mattb on 6/13/2022.
//

#pragma once

#include <map>
#include <meta/midi/MidiLearnable.h>
#include <nlohmann/json.hpp>


class MidiManager
    : public meta::MidiLearnBroadcaster::Listener
{
public:
    using MidiCtrlNumber = int;

    bool isLearning() const { return m_CurrentlyLearning != nullptr; }
    void stopLearn();
    void startLearn(meta::MidiLearnBroadcaster* broadcaster) override;
    void unlearn(meta::MidiLearnBroadcaster* broadcaster) override;
    void addToLearnedList(meta::MidiLearnBroadcaster* broadcaster);
    void processBlock(juce::MidiBuffer& midi);

    void setActiveVoice(int voiceNumber) { m_ActiveVoice = voiceNumber; }

    nlohmann::json getState() const;
    void setState(const nlohmann::json& newState);


private:
    std::vector<meta::MidiLearnBroadcaster*> m_LearnedList;
    std::atomic<meta::MidiLearnBroadcaster*> m_CurrentlyLearning;
    std::atomic<int> m_ActiveVoice;
    std::map<MidiCtrlNumber, std::string> m_GlobalLearnMap;
    juce::MidiKeyboardState m_State;
};
