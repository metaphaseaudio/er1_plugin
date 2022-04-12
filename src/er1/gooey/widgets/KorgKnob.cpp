//
// Created by mzapp on 4/15/18.
//

#include "KorgKnob.h"
#include <meta/util/range.h>

KorgKnob::KorgKnob(juce::AudioParameterFloat& param, float granularity)
    : Slider(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , meta::TimedParameterListener(param)
{
    auto interval = std::abs(param.range.start - param.range.end) / granularity;
    setRange(juce::Range<double>(param.range.start, param.range.end), interval);
    setValue(param, juce::NotificationType::dontSendNotification);
    param.addListener(this);
    addListener(this);

    onDragStart   = [this]() { sliderStartedDragging(); };
    onDragEnd     = [this]() { sliderStoppedDragging(); };
}

void KorgKnob::handleNewParameterValue()
{
    if (!isDragging)
    {
        const auto value = getParameter().getValue();
        setValue(meta::remap_range(getRange(), juce::Range<double>(0.0, 1.0), value), juce::NotificationType::dontSendNotification);
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
        if (!isDragging)
            getParameter().beginChangeGesture();

        getParameter().setValueNotifyingHost(new_value);

        if (!isDragging)
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
