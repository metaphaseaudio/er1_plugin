/*
  ==============================================================================

    OscSectionComponent.cpp
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#include "OscSectionComponent.h"
#include "../../look_and_feel/StandardShapes.h"
#include "../../look_and_feel/ER1Colours.h"

using namespace juce;

OscSectionComponent::OscSectionComponent(GlobalOptions& opts, OscParams& params)
    : r_Opts(opts)
    , m_Header("OSCILLATOR")
    , m_Pitch(WidgetManager::WidgetID::pitch, params.pitch, 0.4f)
    , m_ModDepth(WidgetManager::WidgetID::mod_depth, params.modDepth, 0.0f)
    , m_ModSpeed(WidgetManager::WidgetID::mod_speed, params.modSpeed, 0.5f, 8000)
    , m_ModType(params.modType)
    , m_OscType(params.oscType)
{
    r_Opts.rotary_knobs.addChangeListener(this);
    changeListenerCallback(&r_Opts.rotary_knobs);


    addAndMakeVisible(m_Header);
    addAndMakeVisible(m_Pitch);
    addAndMakeVisible(m_ModSpeed);
    addAndMakeVisible(m_ModDepth);
    addAndMakeVisible(m_ModType);
    addAndMakeVisible(m_OscType);

    m_ModType.setLookAndFeel(&m_LCDLAF);
    m_OscType.setLookAndFeel(&m_LCDLAF);
    m_ModType.setComponentEffect(m_LCDLAF.getLCDFilter());
    m_OscType.setComponentEffect(m_LCDLAF.getLCDFilter());
}

void OscSectionComponent::resized()
{
    m_OscType.setBounds(juce::Rectangle<int>::leftTopRightBottom(760, 138, 864, 157));
    m_ModType.setBounds(juce::Rectangle<int>::leftTopRightBottom(760, 184, 864, 203));
}

void OscSectionComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    bool shouldBeRotary = r_Opts.rotary_knobs.load();
    m_Pitch.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_ModDepth.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_ModSpeed.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
}
