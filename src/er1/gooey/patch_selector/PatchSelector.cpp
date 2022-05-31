//
// Created by Matt on 9/19/2020.
//

#include "PatchSelector.h"
#include "../look_and_feel/StandardShapes.h"

static constexpr int ringButtonCount = 5;

PatchSelector::PatchSelector(juce::ReferenceCountedArray<ER1Sound>& sounds)
{
    for (auto& btn : m_Buttons)
    {
        addAndMakeVisible(btn);
        btn.setRadioGroupId(1);
        btn.onClick = [&]() { sendChangeMessage(); };
    }

    for (int i = 0; i < ringButtonCount; i ++)
    {
        if ((i * 2 + 1) >= sounds.size()) { continue; }
        auto& btn = m_RingButtons.emplace_back(new KorgBooleanParameterButton(*sounds[(i * 2) + 1]->osc.enableRing));
        addAndMakeVisible(*btn);
    }

    m_Buttons[0].setToggleState(true, juce::sendNotification);
}

void PatchSelector::resized()
{
    auto bounds = getLocalBounds();
    auto selectorBtnBounds = StandardShapes::smallRectButton;
    auto ringCtrlBounds = StandardShapes::smallSquareButton;
    auto ringBounds = bounds.removeFromTop(ringCtrlBounds.getHeight());
    bounds.removeFromBottom(ringCtrlBounds.getHeight());
    selectorBtnBounds.setPosition(bounds.getTopLeft());
    const auto offset = (getWidth() - selectorBtnBounds.getWidth() * m_Buttons.size()) / 2.0f;
    selectorBtnBounds = selectorBtnBounds.withX(selectorBtnBounds.getX() + offset);

    for (auto& btn : m_Buttons)
    {
        btn.setBounds(selectorBtnBounds);
        selectorBtnBounds = selectorBtnBounds.withX(selectorBtnBounds.getTopRight().x);
    }

    for (int i = 0; i < m_RingButtons.size(); i++)
    {
        const auto b = i * 2;
        const auto left = m_Buttons[b].getRight();
        const auto right = m_Buttons[b + 1].getX();
        const auto mid = left + ((right - left) / 2);

        ringCtrlBounds.setCentre(mid, ringCtrlBounds.getCentreY());
        m_RingButtons[i]->setBounds(ringCtrlBounds);
    }
}

void PatchSelector::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().removeFromBottom(18);
    const auto offset = (getWidth() - StandardShapes::smallRectButton.getWidth() * m_Buttons.size()) / 2.0f;
    bounds = bounds.withX(bounds.getX() + offset + 5);

    auto analogBounds = bounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 10) - 10);
    g.fillRect(analogBounds);
    bounds.removeFromLeft(10);

    auto audioBounds = bounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 2) - 10);
    g.fillRect(audioBounds);
    bounds.removeFromLeft(10);

    auto pcmBounds = bounds.removeFromLeft((StandardShapes::smallRectButton.getWidth() * 4) - 10);
    g.fillRect(pcmBounds);
}

int PatchSelector::getSelected() const
{
    for (const auto& i_btn : meta::enumerate(m_Buttons)) {
        if (std::get<1>(i_btn).getToggleState())
            { return std::get<0>(i_btn); }
    }
    return -1;
}

