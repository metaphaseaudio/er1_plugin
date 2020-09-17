//
// Created by Matt on 9/15/2020.
//

#pragma once
#include <JuceHeader.h>
#include "KorgButton.h"

class SelectorButton
    : public juce::Component
{
public:
    enum ColourIds
    {
        selectLitColour = 0x1002000,
        selectUnlitColour = 0x1002001
    };

    SelectorButton();
    explicit SelectorButton(std::vector<juce::Component*> icons);

    void addIcon(juce::Component* component);

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    std::vector<juce::Component*> m_Icons;
    juce::Component* p_Selected;
};


