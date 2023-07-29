//
// Created by Matt on 9/19/2020.
//

#include "VoiceSelector.h"
#include "meta/util/container_helpers/array.h"

VoiceSelector::VoiceSelector(MidiManager& midiManager, const std::vector<std::unique_ptr<ER1Voice>>& voices)
    : r_Voices(voices)
{
    setInterceptsMouseClicks(false, true);

    int ring_i = 0;
    for (int i = 0; i < voices.size(); i++)
    {
        auto& voice = voices.at(i);
        auto& btn = m_Buttons.emplace_back(new KorgToggleButton(WidgetManager::WidgetID::sound_btn, i, voice->getControlBlock()->getPatchName()));
        addAndMakeVisible(*btn);
        btn->setRadioGroupId(1);
        btn->onClick = [&](){
            midiManager.setActiveVoice(voice->getControlBlock());
            sendChangeMessage();
        };

        if (voice->getControlBlock()->osc.enableRing != nullptr)
        {
            auto& ringBtn = m_RingButtons.emplace_back(
                new KorgBooleanParameterButton(WidgetManager::WidgetID::ring_btn, ring_i, voice->getControlBlock()->osc.enableRing)
            );
            addAndMakeVisible(*ringBtn);
            ring_i++;
        }
    }

    m_Buttons[0]->setToggleState(true, juce::sendNotification);
    startTimerHz(30);
}

int VoiceSelector::getSelected() const
{

    for (int i = 0; i < m_Buttons.size(); i++)
    {
        if (m_Buttons.at(i)->getToggleState())
            { return i; }
    }
    return -1;
}

void VoiceSelector::timerCallback()
{
    for (int i = 0; i < m_Buttons.size(); i++)
    {
        const auto& voice = r_Voices[i];
        const auto& btn = m_Buttons[i];
        btn->brightness = meta::Interpolate<float>::parabolic(0.0f, 1.0f, voice->getDecayEnvValue(), -5.0f);
        btn->repaint();
    }
}
