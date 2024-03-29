/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "DelaySectionComponent.h"
#include "../../look_and_feel/StandardShapes.h"
#include "../../look_and_feel/ER1Colours.h"

using namespace juce;

DelaySectionComponent::DelaySectionComponent(GlobalOptions& opts, DelayParams& params)
    : m_Header("DELAY")
    , m_Depth(params.depth, 0.0f), m_DepthLabel("Depth Label", "Depth")
    , m_Time(params.time, 0.5f), m_TimeLabel("Time Label", "Time")
    , m_Sync(params.sync), m_SyncLabel("Sync Label", "Tempo\nSync")
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


void DelaySectionComponent::resized()
{
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    m_Header.setBounds(bounds.removeFromTop(labelHeight));
    bounds = bounds.reduced(2);

    auto ctrlBounds = StandardShapes::largeDial;
    auto btnBounds = StandardShapes::smallSquareButton;
    auto labelBounds = juce::Rectangle(bounds).removeFromTop(labelHeight).removeFromLeft(ctrlBounds.getWidth());

    ctrlBounds.setPosition(bounds.getBottomLeft().x, labelBounds.getBottom());
    m_TimeLabel.setBounds(labelBounds); m_Time.setBounds(ctrlBounds);


    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);
    m_DepthLabel.setBounds(labelBounds); m_Depth.setBounds(ctrlBounds);

    ctrlBounds.setPosition(ctrlBounds.getRight(), labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight(), labelBounds.getTopRight().y);
    labelBounds.setHeight(2 * labelHeight);
    btnBounds.setPosition(ctrlBounds.getCentreX() - btnBounds.getWidth() / 2, ctrlBounds.getCentreY() - btnBounds.getWidth() / 2);
    m_SyncLabel.setBounds(labelBounds); m_Sync.setBounds(btnBounds);
}

void DelaySectionComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    bool shouldBeRotary = r_Opts.rotary_knobs.load();
    m_Depth.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_Time.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
}
