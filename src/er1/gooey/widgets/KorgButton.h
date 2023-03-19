//
// Created by mzapp on 4/16/18.
//
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "meta/vst/TimedParameterListener.h"

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
    KorgButton();
    explicit KorgButton(const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    float brightness = 0.0f; // For doing things like flashing buttons
private:
};

class KorgToggleButton
    : public juce::ToggleButton
{
public:
    KorgToggleButton();
    explicit KorgToggleButton(const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;

    float brightness = 0.0f; // For doing things like flashing buttons
    std::function<void(const juce::MouseEvent& event)> onDoubleClick = [](const juce::MouseEvent&) {};

protected:
    void mouseDoubleClick(const juce::MouseEvent& event) override { onDoubleClick(event); };
};


class KorgBooleanParameterButton
    : public KorgToggleButton
    , meta::TimedParameterListener
{
public:
    explicit KorgBooleanParameterButton(juce::AudioParameterBool* param);
    bool isParameterOn() const;
    void buttonClicked();
    void handleNewParameterValue() override;
};