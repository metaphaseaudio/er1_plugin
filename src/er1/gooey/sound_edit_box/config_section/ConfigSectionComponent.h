//
// Created by Mattb on 6/9/2022.
//

#pragma once
#include "LCDScreen.h"


class ConfigSectionComponent
    : public juce::Component
{
public:
    explicit ConfigSectionComponent(ConfigParams& params);
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    LCDScreen m_Screen;
};
