//
// Created by Matt on 1/13/2021.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/vst/TimedParameterListener.h>

class KorgComboBox
    : public juce::ComboBox
    , juce::ComboBox::Listener
    , meta::TimedParameterListener
{
public:
    explicit KorgComboBox(juce::AudioParameterChoice& param);
    void handleNewParameterValue() override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged);
};


