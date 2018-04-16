//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include <gooey/ER1LAF.h>
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
    juce::ScopedPointer<ER1LAF> m_Laf;
    ER1AudioProcessor processor;
    juce::ScopedPointer<ER1AudioProcessorEditor> editor;
};
