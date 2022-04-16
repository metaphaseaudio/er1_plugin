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
}


void KorgButton::paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    static_cast<ER1LAF&>(getLookAndFeel()).drawKorgButton
        (g, *this, isMouseOverButton, isButtonDown);
}

KorgBooleanParameterButton::KorgBooleanParameterButton(juce::AudioParameterBool& param)
    : TimedParameterListener(param)
{
    handleNewParameterValue();
    onClick = [this](){ buttonClicked(); };
}


void KorgBooleanParameterButton::buttonClicked()
{
    if (isParameterOn() != getToggleState())
    {
        getParameter().beginChangeGesture();
        getParameter().setValueNotifyingHost (getToggleState() ? 1.0f : 0.0f);
        getParameter().endChangeGesture();
    }
}

bool KorgBooleanParameterButton::isParameterOn() const
    { return getParameter().getValue() >= 0.5f; }

void KorgBooleanParameterButton::handleNewParameterValue()
    { setToggleState(isParameterOn(), juce::dontSendNotification); }
