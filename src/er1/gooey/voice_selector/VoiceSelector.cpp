//
// Created by Matt on 9/19/2020.
//

#include "VoiceSelector.h"
#include <meta/util/container_helpers/array.h>
#include "../look_and_feel/StandardShapes.h"
#include "Arrows.h"


VoiceSelector::VoiceSelector(MidiManager& midiManager, const std::vector<std::unique_ptr<ER1Voice>>& voices)
    : r_Voices(voices)
    , m_AnalogFooter("PERCUSSION SYNTHESIZER")
    , m_AudioFooter("AUDIO")
    , m_PCMFooter("CH    OH    CR    CL")
{
    addAndMakeVisible(m_AnalogFooter);
    addAndMakeVisible(m_AudioFooter);
    addAndMakeVisible(m_PCMFooter);

    for (auto& voice : voices)
    {
        auto& btn = m_Buttons.emplace_back(new KorgToggleButton(voice->getControlBlock()->name));
        addAndMakeVisible(*btn);
        btn->setRadioGroupId(1);
        btn->onClick = [&](){
            midiManager.setActiveVoice(voice->getControlBlock());
            sendChangeMessage();
        };


        if (voice->getControlBlock()->osc.enableRing != nullptr)
        {
            auto& ringBtn = m_RingButtons.emplace_back(new KorgBooleanParameterButton(voice->getControlBlock()->osc.enableRing));
            addAndMakeVisible(*ringBtn);
            auto& uandr = m_Arrows.emplace_back(new Arrow::UpAndRight());
            addAndMakeVisible(*uandr);
            auto& landd = m_Arrows.emplace_back(new Arrow::UpAndRight(true));
            addAndMakeVisible(*landd);
        }
    }

    m_Buttons[0]->setToggleState(true, juce::sendNotification);
    startTimerHz(30);
}

void VoiceSelector::resized()
{
    auto bounds = getLocalBounds();
    auto selectorBtnBounds = StandardShapes::smallRectButton;
    auto ringCtrlBounds = StandardShapes::smallSquareButton;
    bounds.removeFromTop(ringCtrlBounds.getHeight());
    bounds.removeFromBottom(ringCtrlBounds.getHeight());
    selectorBtnBounds.setPosition(bounds.getTopLeft());

    const auto offset = float(getWidth() - selectorBtnBounds.getWidth() * 16) / 2.0f;
    const auto nonAnalogOffset = offset + selectorBtnBounds.getWidth() * 10;
    selectorBtnBounds = selectorBtnBounds.withX(selectorBtnBounds.getX() + offset);

    for (int i = 0; i < m_Buttons.size(); i++)
    {
        if (i == meta::ER1::ANALOG_SOUND_COUNT)
            { selectorBtnBounds = selectorBtnBounds.withX(nonAnalogOffset); }

        auto& btn = m_Buttons[i];
        btn->setBounds(selectorBtnBounds);
        selectorBtnBounds = selectorBtnBounds.withX(selectorBtnBounds.getTopRight().x);
    }

    for (int i = 0; i < m_RingButtons.size(); i++)
    {
        const bool isLast = i + 1 == m_RingButtons.size();
        const auto b = i * 2;
        const auto& lBtn = m_Buttons[!isLast ? b : meta::ER1::ANALOG_SOUND_COUNT - 1];
        const auto& rBtn = m_Buttons[!isLast ? b + 1 : meta::ER1::ANALOG_SOUND_COUNT];
        auto& ringBtn = m_RingButtons[i];

        const auto left = lBtn->getBounds().getTopLeft().x;
        const auto right = rBtn->getBounds().getTopRight().x;
        const auto mid = left + ((right - left) / 2);

        ringCtrlBounds.setCentre(mid, ringCtrlBounds.getCentreY());
        m_RingButtons[i]->setBounds(ringCtrlBounds);

        const auto leftConnectorBounds = juce::Rectangle<int>(
            left + 8, ringCtrlBounds.getCentreY(),
            ringCtrlBounds.getTopLeft().x - (left + 8),
            lBtn->getBounds().getTopLeft().y - ringCtrlBounds.getCentreY()
        );

        const auto rightConnectorBounds = juce::Rectangle<int>(
            ringCtrlBounds.getBottomRight().x - 1, ringCtrlBounds.getCentreY(),
            (right - 8) - ringCtrlBounds.getBottomRight().x,
            lBtn->getBounds().getTopLeft().y - ringCtrlBounds.getCentreY()
        );

        m_Arrows[i * 2]->setBounds(leftConnectorBounds);
        m_Arrows[i * 2 + 1]->setBounds(rightConnectorBounds);
    }

    auto labelBounds = getLocalBounds().removeFromBottom(18);
    const auto labelOffset = float(getWidth() - StandardShapes::smallRectButton.getWidth() * 16) / 2.0f;
    labelBounds = labelBounds.withX(labelBounds.getX() + labelOffset + 5);

    m_AnalogFooter.setBounds(labelBounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 10) - 10));
    labelBounds.removeFromLeft(10);
    m_AudioFooter.setBounds(labelBounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 2) - 10));
    labelBounds.removeFromLeft(10);
    m_PCMFooter.setBounds(labelBounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 4) - 10));
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
