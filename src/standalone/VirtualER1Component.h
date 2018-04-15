//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include <guts/ER1AudioProcessor.h>
#include <gooey/ER1AudioProcessorEditor.h>

class VirtualER1Component
    : public juce::Component
{
public:
    VirtualER1Component();
    void resized() override;
private:
    ER1AudioProcessor processor;
    ER1AudioProcessorEditor editor;
};
