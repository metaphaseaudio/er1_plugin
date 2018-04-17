//
// Created by mzapp on 4/16/18.
//

#include "Sequencer.h"


Sequencer::Sequencer()
{
    for (int i = 0; i < SEQUENCER_BUTTON_COUNT; i++)
    {
        m_SequencerButtons.emplace_back(new SequencerButton(i));
        addAndMakeVisible(m_SequencerButtons[i].get());
    }
}

void Sequencer::paint(juce::Graphics& g) {}

void Sequencer::resized()
{
    const auto sequencerBounds = getLocalBounds().reduced(2);
    const float btnMargin = 5;
    const float buttonWidth = (getWidth() / static_cast<float>(SEQUENCER_BUTTON_COUNT)) - btnMargin;
    auto btnTopLeftCorner = sequencerBounds.getTopLeft();
    auto btnBtmRightCorner = sequencerBounds.getBottomLeft();
    btnBtmRightCorner.addXY(buttonWidth, 0);

    for (auto& btn : m_SequencerButtons)
    {
        juce::Rectangle<int> btnBounds(btnTopLeftCorner, btnBtmRightCorner);
        btn->setBounds(btnBounds);

        btnTopLeftCorner.addXY(buttonWidth + btnMargin, 0);
        btnBtmRightCorner.addXY(buttonWidth + btnMargin, 0);
    }
}

void Sequencer::buttonClicked(juce::Button* btn)
{
    const int id = dynamic_cast<SequencerButton*>(btn)->stepID;
    juce::BigInteger in;
    in.setBit(id);
    m_Sequence ^= in;
}

