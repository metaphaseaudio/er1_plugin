//
// Created by mzapp on 4/15/18.
//

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/vst/TimedParameterListener.h>
#include "../../guts/LearnableSerializeableParam.h"
#include "../look_and_feel/WidgetManager.h"
#include <meta/gooey/Filmstrip.h>


class KorgKnob
    : public juce::Slider
    , juce::Slider::Listener
    , meta::TimedParameterListener
{
public:
    explicit KorgKnob(WidgetManager::WidgetID id, LearnableSerializeable<juce::AudioParameterFloat>* param, float defaultPosition, float
    granularity=1000.0f);
    void handleNewParameterValue() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void mouseDown(const juce::MouseEvent& e) override;

    void paint(juce::Graphics& graphics) override;

private:
    const WidgetManager::WidgetInfo& getWidget() const;
    void sliderStartedDragging();
    void sliderStoppedDragging();

    bool isDragging = false;
    WidgetManager::WidgetID m_WidgetID;
};
