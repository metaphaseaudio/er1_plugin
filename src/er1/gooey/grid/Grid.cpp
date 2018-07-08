//
// Created by mzapp on 4/16/18.
//

#include "Grid.h"

Grid::Grid()
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        m_Buttons.emplace_back(new GridButton(i));
        addAndMakeVisible(m_Buttons[i].get());
    }
}

void Grid::paint(juce::Graphics& g) {}

void Grid::resized()
{
    const auto sequencerBounds = getLocalBounds().reduced(2);
    const float btnMargin = 5;

    const auto btnHeight = (getHeight() / static_cast<float>(ROW_COUNT)) - btnMargin;
    const auto btnWidth = (getWidth() / static_cast<float>(COL_COUNT)) - btnMargin;
    const juce::Rectangle<float> btnDimensions(btnWidth, btnHeight);

    for (int row = 0; row < ROW_COUNT; row++)
    {
        const auto firstID = COL_COUNT * row;
        const auto rowTop = ((row + 1) * btnMargin) + (row * btnHeight);

        for (int col = 0; col < COL_COUNT; col++)
        {
            const auto colLeft = ((col + 1) * btnMargin) + (col * btnWidth);
            const auto btnID = firstID + col;
            auto& btn = m_Buttons[btnID];
            btn->setBounds(btnDimensions.toNearestInt());
            btn->setTopLeftPosition(colLeft, rowTop);
        }
    }
}

void Grid::buttonClicked(juce::Button* btn)
{
    const int id = dynamic_cast<GridButton*>(btn)->stepID;
    juce::BigInteger in;
    in.setBit(id);
    m_Sequence ^= in;
}

