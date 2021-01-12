//
// Created by mzapp on 4/15/18.
//

#pragma once

#include <JuceHeader.h>
#include <meta/vst/TimedParameterListener.h>

class KorgKnob
    : public juce::Slider
    , juce::Slider::Listener
    , meta::TimedParameterListener
{
public:
    KorgKnob(juce::AudioParameterFloat& param);
    void handleNewParameterValue() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    void sliderStartedDragging();
    void sliderStoppedDragging();

    bool isDragging = false;
};
