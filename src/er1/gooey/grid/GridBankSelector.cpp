//
// Created by mzapp on 7/8/18.
//

#include "GridBankSelector.h"

GridBankSelector::GridBankSelector()
{
    for (int i = 0; i < BTN_COUNT; i++)
    {
        m_BankButtons.emplace_back(std::make_unique<KorgButton>(juce::String(i)));
        addAndMakeVisible(m_BankButtons.at(i).get());
        m_BankButtons.at(i)->addListener(this);
    }
}

void GridBankSelector::resized()
{
    const int btnMargin = 5;
    const auto btnWidth = (getWidth() / static_cast<float>(BTN_COUNT)) - btnMargin;
    auto bounds = getLocalBounds().reduced(2);
    for (auto& btn : m_BankButtons)
    {
        btn->setBounds(bounds.removeFromLeft(btnWidth));
        bounds.removeFromLeft(btnMargin);
    }
}

void GridBankSelector::buttonClicked(juce::Button *btn)
{

}
