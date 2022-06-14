//
// Created by mzapp on 4/15/18.
//

#include "KorgKnob.h"
#include <meta/util/range.h>

KorgKnob::KorgKnob(juce::AudioParameterFloat* param, float granularity)
    : Slider(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , meta::TimedParameterListener(param)
{
    if (param == nullptr)
    {
        setEnabled(false);
        return;
    }

    auto interval = std::abs(param->range.start - param->range.end) / granularity;
    setRange(juce::Range<double>(param->range.start, param->range.end), interval);
    setValue(*param, juce::NotificationType::dontSendNotification);
    param->addListener(this);

    juce::Slider::addListener(this);

    onDragStart   = [this]() { sliderStartedDragging(); };
    onDragEnd     = [this]() { sliderStoppedDragging(); };
}

void KorgKnob::handleNewParameterValue()
{
    if (p_Parameter != nullptr && !isDragging)
    {
        const auto value = p_Parameter->getValue();
        setValue(meta::remap_range(getRange().getStart(), getRange().getEnd(), 0.0, 1.0, value), juce::NotificationType::dontSendNotification);
        repaint();
    }
}


void KorgKnob::sliderValueChanged(juce::Slider* slider)
{
    if (slider != this) { return; }

    const auto new_value = meta::remap_range(0.0f, 1.f, getRange().getStart(), getRange().getEnd(), static_cast<double>(getValue()));

    if (p_Parameter != nullptr && p_Parameter->getValue() != new_value)
    {
        if (!isDragging)
            p_Parameter->beginChangeGesture();

        p_Parameter->setValueNotifyingHost(new_value);

        if (!isDragging)
            p_Parameter->endChangeGesture();
    }
}

void KorgKnob::sliderStartedDragging()
{
    isDragging = true;
    if (p_Parameter != nullptr) { p_Parameter->beginChangeGesture(); }
}

void KorgKnob::sliderStoppedDragging()
{
    isDragging = false;
    if (p_Parameter != nullptr) { p_Parameter->endChangeGesture(); }
}

void KorgKnob::mouseDown(const juce::MouseEvent& e)
{
    juce::Slider::mouseDown(e);
    if (!e.mods.isPopupMenu() || p_Parameter == nullptr)
        { return; }

    juce::PopupMenu learn;
    learn.addItem(1, "MIDI Learn");
    learn.addItem(1, "MIDI Un-learn");

    learn.showMenuAsync(juce::PopupMenu::Options(), [this] (int result)
    {
        if (result == 0) { return; }
        if (result == 1) { sendLearn(); }
        if (result == 2) { sendUnlearn(); }
    });
}

void KorgKnob::handleMidiMessage(const juce::MidiMessage& message)
{
    if (p_Parameter != nullptr)
    {
        p_Parameter->setValueNotifyingHost(message.getControllerValue() / 127.0f);
    }
}
