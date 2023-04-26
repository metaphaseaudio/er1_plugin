//
// Created by Matt on 9/19/2020.
//

#include "VoiceSelector.h"
#include <meta/util/container_helpers/array.h>
#include "../look_and_feel/StandardShapes.h"
#include "Arrows.h"


VoiceSelector::VoiceSelector(MidiManager& midiManager, const std::vector<std::unique_ptr<ER1Voice>>& voices)
    : r_Voices(voices)
{
    setInterceptsMouseClicks(false, true);

    for (int i = voices.size(); --i > 0;)
    {
        auto& voice = voices.at(i);
        auto& btn = m_Buttons.emplace_back(new KorgToggleButton(WidgetManager::WidgetID::sound_btn, i, voice->getControlBlock()->getPatchName()));
        addAndMakeVisible(*btn);
        btn->setRadioGroupId(1);
        btn->onClick = [&](){
            midiManager.setActiveVoice(voice->getControlBlock());
            sendChangeMessage();
        };

//        if (voice->getControlBlock()->osc.enableRing != nullptr)
//        {
//            auto& ringBtn = m_RingButtons.emplace_back(new KorgBooleanParameterButton(voice->getControlBlock()->osc.enableRing));
//            addAndMakeVisible(*ringBtn);
//            auto& uandr = m_Arrows.emplace_back(new Arrow::UpAndRight());
//            addAndMakeVisible(*uandr);
//            auto& landd = m_Arrows.emplace_back(new Arrow::UpAndRight(true));
//            addAndMakeVisible(*landd);
//        }
    }

    m_Buttons[0]->setToggleState(true, juce::sendNotification);
    startTimerHz(30);
}

int VoiceSelector::getSelected() const
{
    for (const auto& i_btn : meta::enumerate(m_Buttons)) {
        if (std::get<1>(i_btn)->getToggleState())
            { return std::get<0>(i_btn); }
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
