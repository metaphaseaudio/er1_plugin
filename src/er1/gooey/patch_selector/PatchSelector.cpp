//
// Created by Matt on 9/19/2020.
//

#include "PatchSelector.h"
#include "../look_and_feel/ER1Colours.h"
#include "../look_and_feel/StandardShapes.h"


PatchSelector::PatchSelector()
{
    for (auto& btn : m_Buttons)
    {
        addAndMakeVisible(btn);
        btn.setRadioGroupId(1);
        btn.addListener(this);
    }

    for (auto& btn : m_RingButtons)
    {
        addAndMakeVisible(btn);
        btn.addListener(this);
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

    for (int i = 0; i < m_RingButtons.size() - 2; i++)
    {
        const auto b = i * 2;
        const auto left = m_Buttons[b].getRight();
        const auto right = m_Buttons[b + 1].getX();
        const auto mid = left + ((right - left) / 2);

        ringCtrlBounds.setCentre(mid, ringCtrlBounds.getCentreY());
        m_RingButtons[i].setBounds(ringCtrlBounds);
    }
}

void PatchSelector::paint(juce::Graphics& g) {}


void PatchSelector::buttonClicked(juce::Button* btn)
{

}
