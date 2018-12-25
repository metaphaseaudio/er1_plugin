//
// Created by mzapp on 4/16/18.
//

#include "KorgButton.h"
#include "../look_and_feel/ER1LAF.h"


KorgButton::KorgButton()
    : juce::Button("")
{};

KorgButton::KorgButton(const juce::String& name)
    : juce::Button(name)
{}

KorgToggleButton::KorgToggleButton()
    : juce::ToggleButton("")
{};

KorgToggleButton::KorgToggleButton(const juce::String& name)
    : juce::ToggleButton(name)
{}

void KorgToggleButton::paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    static_cast<ER1LAF&>(getLookAndFeel()).drawKorgToggleButton
            (g, *this, isMouseOverButton, isButtonDown);
};


void KorgButton::paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    static_cast<ER1LAF&>(getLookAndFeel()).drawKorgButton
        (g, *this, isMouseOverButton, isButtonDown);
}
