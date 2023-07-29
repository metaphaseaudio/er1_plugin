/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "AmpSectionComponent.h"
#include "../../look_and_feel/ER1Colours.h"

using namespace juce;

AmpSectionComponent::AmpSectionComponent(GlobalOptions& opts, AmpParams& params)
    : m_Header("AMP")
    , m_Decay(WidgetManager::WidgetID::decay, params.decay, 0.5f)
    , m_Level(WidgetManager::WidgetID::level, params.level, 0.6f)
    , m_Pan(WidgetManager::WidgetID::pan, params.pan, 0.0f)
    , m_LowBoost(WidgetManager::WidgetID::low_boost, params.lowBoost, 0.0f)
    , r_Opts(opts)
{
    r_Opts.rotary_knobs.addChangeListener(this);
    changeListenerCallback(&r_Opts.rotary_knobs);

    addAndMakeVisible(m_Header);
    addAndMakeVisible(m_Decay);
    addAndMakeVisible(m_Level);
    addAndMakeVisible(m_Pan);
    addAndMakeVisible(m_LowBoost);
}


void AmpSectionComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    bool shouldBeRotary = r_Opts.rotary_knobs.load();
    m_Decay.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_Level.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_Pan.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_LowBoost.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
}