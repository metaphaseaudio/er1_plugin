//
// Created by Mattb on 6/13/2022.
//

#include "MidiManager.h"

void MidiManager::stopLearn()
{
    m_CurrentlyLearning = nullptr;
}

void MidiManager::processBlock(juce::MidiBuffer& midi)
{
    for (const auto event : midi)
    {
        const auto& message = event.getMessage();
        if (message.isController())
        {
            const auto ctrlNumber = message.getControllerNumber();
            if (isLearning())
            {
                m_LearnMap[ctrlNumber] = m_CurrentlyLearning;
                stopLearn();
            }

            if (m_LearnMap.contains(ctrlNumber))
                { m_LearnMap[ctrlNumber]->handleMidiMessage(message); }
        }
    }
}


void MidiManager::learn(meta::MidiLearnBroadcaster* broadcaster)
    { m_CurrentlyLearning = broadcaster; }

void MidiManager::unlearn(meta::MidiLearnBroadcaster* broadcaster)
{
    // Find the key
    int key = -1;
    for (auto& kv : m_LearnMap)
    {
        if (std::get<1>(kv) == broadcaster)
            { key = std::get<0>(kv); }
    }

    if (key != -1)
        { m_LearnMap.erase(key); }
}

