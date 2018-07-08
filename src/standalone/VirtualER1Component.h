//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include <gooey/look_and_feel/ER1LAF.h>
#include <guts/ER1AudioProcessor.h>
#include <gooey/ER1AudioProcessorEditor.h>

class VirtualER1Component
    : public juce::Component
{
public:
    VirtualER1Component();
    ~VirtualER1Component();
    void resized() override;

private:

    ER1AudioProcessor processor;
    juce::ScopedPointer<ER1LAF> m_Laf;
    juce::ScopedPointer<ER1AudioProcessorEditor> editor;
};


juce::ApplicationCommandManager& getCommandManager();
juce::ApplicationProperties& getAppProperties();
bool isOnTouchDevice();