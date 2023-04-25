//
// Created by mzapp on 4/15/18.
//

#include "KorgKnob.h"
#include "../look_and_feel/ER1LAF.h"
#include <meta/util/range.h>

KorgKnob::KorgKnob(WidgetManager::WidgetID id, LearnableSerializeable<juce::AudioParameterFloat>* param, float defaultPosition, float granularity)
    : Slider(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox)
    , meta::TimedParameterListener(param)
    , m_WidgetID(id)
{
    if (param == nullptr)
    {
        setEnabled(false);
        return;
    }

    auto& range = param->getNormalisableRange();
    auto interval = std::abs(range.start - range.end) / granularity;
    setRange(juce::Range<double>(range.start, range.end), interval);
    setValue(*param, juce::NotificationType::dontSendNotification);
    setDoubleClickReturnValue(true, defaultPosition);

    juce::Slider::addListener(this);

    onDragStart   = [this]() { sliderStartedDragging(); };
    onDragEnd     = [this]() { sliderStoppedDragging(); };

    auto& widget = getWidget();
    auto dimension = widget.filmstrip.getFrameDimensions();
    setSize(dimension.getWidth(), dimension.getHeight());
    setTopLeftPosition(widget.position);
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
    learn.addItem(2, "MIDI Un-startLearn");

    learn.showMenuAsync(juce::PopupMenu::Options(), [this] (int result)
    {
        if (result == 0) { return; }
        if (result == 1) { dynamic_cast<meta::MidiLearnBroadcaster*>(p_Parameter)->sendLearn(); }
        if (result == 2) { dynamic_cast<meta::MidiLearnBroadcaster*>(p_Parameter)->sendUnlearn(); }
    });
}

void KorgKnob::paint(juce::Graphics& graphics)
{
    auto& widget = getWidget();
    int frame = valueToProportionOfLength(getValue()) * (widget.filmstrip.getNFrames() - 1);
    graphics.drawImage(widget.filmstrip.getFrame(frame), getLocalBounds().toFloat());
}

const WidgetManager::WidgetInfo& KorgKnob::getWidget() const
{
    auto& laf = getLookAndFeel();
    auto er1_laf = dynamic_cast<ER1LAF*>(&laf);
    return er1_laf->getWidgetInfo(m_WidgetID, WidgetManager::WidgetVariant::standard, 0);
}
