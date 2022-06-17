//
// Created by Mattb on 6/13/2022.
//

#include "MidiManager.h"
#include <algorithm>

using json = nlohmann::json;

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
            if (isLearning())
            {
                auto learned = m_CurrentlyLearning.load();
                learned->setLearnedControl(message);
                m_LearnedList.push_back(learned);
                stopLearn();
            }

            for (auto& param : m_LearnedList)
                { param->handleMidiMessage(message); }
        }
    }
}


void MidiManager::learn(meta::MidiLearnBroadcaster* broadcaster)
    { m_CurrentlyLearning = dynamic_cast<meta::MidiLearnableAudioParameterFloat*>(broadcaster); }

void MidiManager::unlearn(meta::MidiLearnBroadcaster* broadcaster)
{
    m_LearnedList.erase(
        std::remove_if(m_LearnedList.begin(), m_LearnedList.end(), [&](auto* item) { return item == broadcaster; }),
        m_LearnedList.end()
    );
}

json MidiManager::getState() const
{
    std::vector<json> learnedList;

    for (auto& learned : m_LearnedList)
    {
        learnedList.push_back({
            {"param", learned->name.toStdString()},
            {"ctrl", learned->getLearnedControl().getControllerNumber()},
            {"chan", learned->getLearnedControl().getChannel()},
        });
    }

    return {
        {"learned", learnedList},
    };
}

void MidiManager::setState(const json& newState)
{

}

