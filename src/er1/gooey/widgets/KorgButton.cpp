//
// Created by mzapp on 4/16/18.
//

#include "KorgButton.h"
#include "../look_and_feel/ER1LAF.h"
#include "../look_and_feel/ER1Colours.h"


KorgButton::KorgButton(WidgetManager::WidgetID id, int index)
    : juce::Button("")
    , m_WidgetID(id)
    , m_Index(index)
{};

KorgButton::KorgButton(WidgetManager::WidgetID id, int index, const juce::String& name)
    : juce::Button(name)
    , m_WidgetID(id)
    , m_Index(index)
{}

KorgToggleButton::KorgToggleButton(WidgetManager::WidgetID id, int index)
    : juce::ToggleButton("")
    , m_WidgetID(id)
    , m_Index(index)
{
    auto& widget = dynamic_cast<ER1LAF*>(&getLookAndFeel())->getWidgetInfo(m_WidgetID, WidgetManager::WidgetVariant::standard, m_Index);
    setSize(widget.filmstrip.getFrameDimensions().getWidth(), widget.filmstrip.getFrameDimensions().getHeight());
    setTopLeftPosition(widget.position);
};

KorgToggleButton::KorgToggleButton(WidgetManager::WidgetID id, int index, const juce::String& name)
    : juce::ToggleButton(name)
    , m_WidgetID(id)
    , m_Index(index)
{
    auto& widget = dynamic_cast<ER1LAF*>(&getLookAndFeel())->getWidgetInfo(m_WidgetID, WidgetManager::WidgetVariant::standard, m_Index);
    setSize(widget.filmstrip.getFrameDimensions().getWidth(), widget.filmstrip.getFrameDimensions().getHeight());
    setTopLeftPosition(widget.position);
}


void KorgToggleButton::paintButton(juce::Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
    auto toggleLit = getToggleState();
    auto variant = isMouseOverButton ? WidgetManager::WidgetVariant::hover : WidgetManager::WidgetVariant::standard;
    auto& widget = dynamic_cast<ER1LAF&>(getLookAndFeel()).getWidgetInfo(m_WidgetID, variant, m_Index);
    auto frame = (widget.filmstrip.getNFrames() - 1) * (toggleLit ? brightness : 1.0 - brightness);
    g.drawImage(widget.filmstrip.getFrame(int(frame)), getLocalBounds().toFloat());
}



KorgBooleanParameterButton::KorgBooleanParameterButton(WidgetManager::WidgetID id, int index, juce::AudioParameterBool* param)
    : TimedParameterListener(param)
    , KorgToggleButton(id, index)
{
    if (param == nullptr) { setEnabled(false); }
    handleNewParameterValue();
    onClick = [this](){ buttonClicked(); };
}


void KorgBooleanParameterButton::buttonClicked()
{
    if (isParameterOn() != getToggleState() && p_Parameter != nullptr)
    {
        p_Parameter->beginChangeGesture();
        p_Parameter->setValueNotifyingHost (getToggleState() ? 1.0f : 0.0f);
        p_Parameter->endChangeGesture();
    }
}

bool KorgBooleanParameterButton::isParameterOn() const
    { return p_Parameter != nullptr && p_Parameter->getValue() >= 0.5f; }

void KorgBooleanParameterButton::handleNewParameterValue()
    { setToggleState(isParameterOn(), juce::dontSendNotification); }
