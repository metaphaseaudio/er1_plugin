//
// Created by Mattb on 6/13/2022.
//

#include "MidiManager.h"
#include <algorithm>

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
                auto learned = m_CurrentlyLearning.load();
                learned->setLearnedCtrlNumber(ctrlNumber);
                m_LearnedList.push_back(learned);
                stopLearn();
            }

            for (auto& param : m_LearnedList)
            {
                if (param->getLearnedCtrlNumber() == ctrlNumber)
                {
                    param->handleMidiMessage(message);
                }
            }
        }
    }
}


void MidiManager::learn(meta::MidiLearnBroadcaster* broadcaster)
    { m_CurrentlyLearning = broadcaster; }

void MidiManager::unlearn(meta::MidiLearnBroadcaster* broadcaster)
{
    m_LearnedList.erase(
        std::remove_if(m_LearnedList.begin(), m_LearnedList.end(), [&](meta::MidiLearnBroadcaster* item)
        {
            return item == broadcaster;
        }),

        m_LearnedList.end()
    );
}

