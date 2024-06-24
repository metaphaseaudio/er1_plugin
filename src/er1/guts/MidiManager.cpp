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
        if (message.isNoteOn() && m_IsListening)
        {
            m_ActiveVoice.load()->config->note = message.getNoteNumber();
            m_ActiveVoice.load()->config->chan = message.getChannel();
            m_IsListening = false;
            sendChangeMessage();
        }
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


void MidiManager::startLearn(meta::MidiLearnBroadcaster* broadcaster)
    { m_CurrentlyLearning = broadcaster; }

void MidiManager::unlearn(meta::MidiLearnBroadcaster* broadcaster)
{
    m_LearnedList.erase(
        std::remove_if(m_LearnedList.begin(), m_LearnedList.end(), [&](auto* item) { return item == broadcaster; }),
        m_LearnedList.end()
    );
}

json MidiManager::getState() const{return {};}
void MidiManager::setState(const json& newState){}

void MidiManager::addToLearnedList(meta::MidiLearnBroadcaster* broadcaster)
    { m_LearnedList.push_back(broadcaster); }

