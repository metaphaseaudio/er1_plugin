//
// Created by mzapp on 4/16/18.
//
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "meta/vst/TimedParameterListener.h"
#include "../look_and_feel/WidgetManager.h"

class DoubleClickable
    : public juce::Component
{
public:
    DoubleClickable() : onDoubleClick([](const juce::MouseEvent&){}) {};
    std::function<void(const juce::MouseEvent& event)> onDoubleClick;
};


class KorgButton
    : public juce::Button
{
public:
    KorgButton(WidgetManager::WidgetID id, int index);
    KorgButton(WidgetManager::WidgetID id, int index, const juce::String& name);

    float brightness = 0.0f; // For doing things like flashing buttons

private:
    WidgetManager::WidgetID m_WidgetID;
    int m_Index;
};

class KorgToggleButton
    : public juce::ToggleButton
{
public:
    KorgToggleButton(WidgetManager::WidgetID id, int index);
    explicit KorgToggleButton(WidgetManager::WidgetID id, int index, const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    float brightness = 0.0f; // For doing things like flashing buttons runs. 0 to 1.
    std::function<void(const juce::MouseEvent& event)> onDoubleClick = [](const juce::MouseEvent&) {};

protected:
    void mouseDoubleClick(const juce::MouseEvent& event) override { onDoubleClick(event); };

private:
    WidgetManager::WidgetID m_WidgetID;
    int m_Index;
};


class KorgBooleanParameterButton
    : public KorgToggleButton
    , meta::TimedParameterListener
{
public:
    KorgBooleanParameterButton(WidgetManager::WidgetID id, int index, juce::AudioParameterBool* param);
    bool isParameterOn() const;
    void buttonClicked();
    void handleNewParameterValue() override;
};