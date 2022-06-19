//
// Created by mzapp on 4/15/18.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/vst/TimedParameterListener.h>
#include "../../guts/LearnableSerializeableProcessorParamFloat.h"

class KorgKnob
    : public juce::Slider
    , juce::Slider::Listener
    , meta::TimedParameterListener
{
public:
    explicit KorgKnob(LearnableSerializeable<juce::AudioParameterFloat>* param, float granularity=1000.0f);
    void handleNewParameterValue() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void mouseDown(const juce::MouseEvent& e) override;

private:
    void sliderStartedDragging();
    void sliderStoppedDragging();

    bool isDragging = false;
};
