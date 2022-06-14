//
// Created by Mattb on 6/13/2022.
//

#pragma once

#include <map>
#include <meta/midi/MidiLearnable.h>


class MidiManager
    : public meta::MidiLearnBroadcaster::Listener
{
public:
    using MidiCtrlNumber = int;

    bool isLearning() const { return m_CurrentlyLearning != nullptr; }
    void stopLearn();
    void learn(meta::MidiLearnBroadcaster* broadcaster) override;
    void unlearn(meta::MidiLearnBroadcaster* broadcaster) override;
    void processBlock(juce::MidiBuffer& midi);

private:
    std::atomic<meta::MidiLearnBroadcaster*> m_CurrentlyLearning;
    juce::MidiKeyboardState m_State;
    std::map<MidiCtrlNumber, meta::MidiLearnBroadcaster*> m_LearnMap;
};
