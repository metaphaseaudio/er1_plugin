//
// Created by mzapp on 4/15/18.
//

#include "KorgKnob.h"

KorgKnob::KorgKnob(juce::AudioParameterFloat& param)
    : Slider(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , meta::TimedParameterListener(param)
{ addListener(this); }

void KorgKnob::handleNewParameterValue()
{
    setValue(getParameter().getValue(), juce::NotificationType::dontSendNotification);
    repaint();
}

void KorgKnob::sliderValueChanged(juce::Slider* slider)
{
    if (slider != this) { return; }
    getParameter().setValue(static_cast<float>(getValue()));
}
