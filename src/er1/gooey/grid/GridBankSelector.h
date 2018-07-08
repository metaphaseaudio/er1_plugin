//
// Created by mzapp on 7/8/18.
//
#pragma once

#include <JuceHeader.h>
#include "../widgets/KorgButton.h"

class GridBankSelector
    : public juce::Component
    , juce::Button::Listener
{
    constexpr static int BTN_COUNT = 4;

public:
    GridBankSelector();
    void resized() override;
    void buttonClicked(juce::Button* btn) override;
private:
    std::vector<std::unique_ptr<KorgButton>> m_BankButtons;
};
