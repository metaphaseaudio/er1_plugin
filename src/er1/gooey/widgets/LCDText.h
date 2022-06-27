//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LCDText
    : public juce::Label
    , juce::Timer
{
public:
    enum ColourIds
    {
        textColour = 0x1022CD1,
        lcdColour = 0x1022CD2,
        bezelColour = 0x1022CD3
    };


    LCDText(const std::string& componentName, const juce::String& text, float rotate_speed=0.5);
    juce::TextEditor* createEditorComponent() override;
    void timerCallback() override;

private:
    float m_RotateSpeed;
};


