//
// Created by Matt on 9/15/2020.
//

#pragma once
#include <JuceHeader.h>
#include "KorgButton.h"

class SelectorButton
    : public juce::Component
    , juce::Button::Listener
{
public:
    enum ColourIds
    {
        selectLitColour = 0x1002000,
        selectUnlitColour = 0x1002001
    };

    SelectorButton(const std::initializer_list<juce::Component*>& icons);

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    KorgButton m_Next;
    std::vector<juce::Component*> m_Icons;
    juce::Component* p_Selected;
};


