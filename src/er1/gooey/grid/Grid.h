//
// Created by mzapp on 4/16/18.
//

#include <JuceHeader.h>
#include "GridButton.h"

class Grid
    : public juce::Component
    , juce::Button::Listener
{
    constexpr static unsigned int ROW_COUNT = {4};
    constexpr static unsigned int COL_COUNT = {4};
    constexpr static unsigned int BUTTON_COUNT = {COL_COUNT * ROW_COUNT};

public:
    Grid();
    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button*) override;

private:
    std::vector<std::unique_ptr<GridButton>> m_Buttons;
    juce::BigInteger m_Sequence;
};
