//
// Created by mzapp on 4/16/18.
//
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "meta/vst/TimedParameterListener.h"

class KorgButton
    : public juce::Button
{
public:
    KorgButton();
    explicit KorgButton(const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
};

class KorgToggleButton
    : public juce::ToggleButton
{
public:
    KorgToggleButton();
    explicit KorgToggleButton(const juce::String& name);
    void paintButton(juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
};


class KorgBooleanParameterButton
    : public KorgToggleButton
    , meta::TimedParameterListener
{
public:
    explicit KorgBooleanParameterButton(juce::AudioParameterBool& param);
    bool isParameterOn() const;
    void buttonClicked();
    void handleNewParameterValue() override;
};