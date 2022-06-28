//
// Created by Mattb on 6/27/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>


class Header
    : public juce::Component
{
public:
    using juce::Component::Component;
    void paint(juce::Graphics& g) override;
};
