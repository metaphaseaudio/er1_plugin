/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "DelaySectionComponent.h"
#include "../../look_and_feel/ER1Colours.h"

using namespace juce;

DelaySectionComponent::DelaySectionComponent(GlobalOptions& opts, DelayParams& params)
    : m_Header("DELAY")
    , m_Depth(WidgetManager::WidgetID::delay_depth, params.depth, 0.0f), m_DepthLabel("Depth Label", "Depth")
    , m_Time(WidgetManager::WidgetID::delay_time, params.time, 0.5f), m_TimeLabel("Time Label", "Time")
    , m_Sync(WidgetManager::WidgetID::tempo_sync, 0, params.sync), m_SyncLabel("Sync Label", "Tempo\nSync")
    , r_Opts(opts)
{
    r_Opts.rotary_knobs.addChangeListener(this);
    changeListenerCallback(&r_Opts.rotary_knobs);

    m_DepthLabel.setJustificationType(juce::Justification::centred);
    m_TimeLabel.setJustificationType(juce::Justification::centred);
    m_SyncLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Header);
    addAndMakeVisible(m_Depth); addAndMakeVisible(m_DepthLabel);
    addAndMakeVisible(m_Time); addAndMakeVisible(m_TimeLabel);
    addAndMakeVisible(m_Sync); addAndMakeVisible(m_SyncLabel);
}


void DelaySectionComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    bool shouldBeRotary = r_Opts.rotary_knobs.load();
    m_Depth.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_Time.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
}
