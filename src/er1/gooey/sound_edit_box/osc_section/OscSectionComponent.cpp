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
    , m_Pitch(params.pitch, 0.4f), m_PitchLabel("Pitch Label", "Pitch")
    , m_ModDepth(params.modDepth, 0.0f), m_ModDepthLabel("Mod Depth Label", "Mod Depth")
    , m_ModSpeed(params.modSpeed, 0.5f, 8000), m_ModSpeedLabel("Mod Speed Label", "Mod Speed")
    , m_ModType(params.modType), m_ModTypeLabel("Mod Type Label", "Mod Type")
    , m_OscType(params.oscType), m_OscTypeLabel("Osc Type Label", "Osc Type")
{
    r_Opts.rotary_knobs.addChangeListener(this);
    changeListenerCallback(&r_Opts.rotary_knobs);

    m_PitchLabel.setJustificationType(juce::Justification::centred);
    m_ModSpeedLabel.setJustificationType(juce::Justification::centred);
    m_ModDepthLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Header);
    addAndMakeVisible(m_Pitch);    addAndMakeVisible(m_PitchLabel);
    addAndMakeVisible(m_ModSpeed); addAndMakeVisible(m_ModSpeedLabel);
    addAndMakeVisible(m_ModDepth); addAndMakeVisible(m_ModDepthLabel);
    addAndMakeVisible(m_ModType);  addAndMakeVisible(m_ModTypeLabel);
    addAndMakeVisible(m_OscType);  addAndMakeVisible(m_OscTypeLabel);
}

void OscSectionComponent::resized()
{
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    m_Header.setBounds(bounds.removeFromTop(labelHeight));
    bounds = bounds.reduced(2);

    auto ctrlBounds = StandardShapes::largeDial;
    auto selectorBounds = bounds.removeFromRight(bounds.getWidth() - ((ctrlBounds.getWidth() + margin) * 3));

    m_OscTypeLabel.setBounds(selectorBounds.removeFromTop(labelHeight)); m_OscType.setBounds(selectorBounds.removeFromTop(labelHeight));
    selectorBounds.removeFromTop(5);
    m_ModTypeLabel.setBounds(selectorBounds.removeFromTop(labelHeight)); m_ModType.setBounds(selectorBounds.removeFromTop(labelHeight));

    auto labelBounds = bounds.removeFromTop(labelHeight).removeFromLeft(ctrlBounds.getWidth());
    ctrlBounds.setPosition(bounds.getBottomLeft().x, labelBounds.getBottom());

    m_PitchLabel.setBounds(labelBounds); m_Pitch.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_ModSpeedLabel.setBounds(labelBounds); m_ModSpeed.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_ModDepthLabel.setBounds(labelBounds); m_ModDepth.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);
}

void OscSectionComponent::changeListenerCallback(ChangeBroadcaster* source)
{
    bool shouldBeRotary = r_Opts.rotary_knobs.load();
    m_Pitch.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_ModDepth.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
    m_ModSpeed.setSliderStyle(shouldBeRotary ? juce::Slider::SliderStyle::Rotary : juce::Slider::SliderStyle::RotaryVerticalDrag);
}
