//
// Created by mzapp on 4/15/18.
//

#include "KorgKnob.h"
#include <meta/util/range.h>

KorgKnob::KorgKnob(juce::AudioParameterFloat& param)
    : Slider(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , meta::TimedParameterListener(param)
{
    auto interval = std::abs(param.range.start - param.range.end) / 100.0f;
    setRange(juce::Range<float>(param.range.start, param.range.end), interval);
    addListener(this);

    onDragStart   = [this]() { sliderStartedDragging(); };
    onDragEnd     = [this]() { sliderStoppedDragging(); };
}

void KorgKnob::handleNewParameterValue()
{
    if (! isDragging)
    {
        setValue(getParameter().getValue(), juce::NotificationType::dontSendNotification);
        repaint();
    }
}



void KorgKnob::sliderValueChanged(juce::Slider* slider)
{
    if (slider != this) { return; }

    const auto normalized_range = juce::Range<double>(0.0f, 1.f);
    const auto new_value = meta::remap_range(normalized_range, getRange(), static_cast<double>(getValue()));

    if (getParameter().getValue() != new_value)
    {
        if (! isDragging)
            getParameter().beginChangeGesture();

        getParameter().setValueNotifyingHost(new_value);

        if (! isDragging)
            getParameter().endChangeGesture();
    }
}

void KorgKnob::sliderStartedDragging()
{
    isDragging = true;
    getParameter().beginChangeGesture();
}

void KorgKnob::sliderStoppedDragging()
{
    isDragging = false;
    getParameter().endChangeGesture();
}
