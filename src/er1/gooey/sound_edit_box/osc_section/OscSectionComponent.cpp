/*
  ==============================================================================

    OscSectionComponent.cpp
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#include "OscSectionComponent.h"

using namespace juce;

OscSectionComponent::OscSectionComponent()
    : m_Pitch("Pitch"),        m_PitchLabel("Pitch Label", "Pitch Label")
    , m_ModDepth("Mod Depth"), m_ModDepthLabel("Mod Depth Label", "Mod Depth")
    , m_ModSpeed("Mod Speed"), m_ModSpeedLabel("Mod Speed Label", "Mod Speed")
    , m_ModType("Mod Type"),   m_ModTypeLabel("Mod Type Label", "Mod Type")
    , m_OscType("Osc Type"),   m_OscTypeLabel("Osc Type Label", "Osc Type")
{
    m_Pitch.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_ModDepth.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_ModSpeed.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_ModType.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    addAndMakeVisible(m_Pitch);    addAndMakeVisible(m_PitchLabel);
    addAndMakeVisible(m_ModDepth); addAndMakeVisible(m_ModDepthLabel);
    addAndMakeVisible(m_ModSpeed); addAndMakeVisible(m_ModSpeedLabel);
    addAndMakeVisible(m_ModType);  addAndMakeVisible(m_ModTypeLabel);
    addAndMakeVisible(m_OscType);  addAndMakeVisible(m_OscTypeLabel);
}

OscSectionComponent::~OscSectionComponent() {}

void OscSectionComponent::paint (Graphics& g)
{
    auto header = getLocalBounds().removeFromTop(22);

    g.setColour(Colours::black);
    g.fillRect(header);

    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.drawFittedText("OSCILLATOR", header, juce::Justification::centred, 1);
}

void OscSectionComponent::resized()
{
    const auto labelHeight = 22;
    auto bounds = getLocalBounds();
    bounds.removeFromTop(22);
    bounds = bounds.reduced(2);

    auto upperCtrls = bounds.removeFromTop(bounds.getHeight() / 2);

    auto ctrlThirds = bounds.getWidth() / 3;
    auto pitchBounds = upperCtrls.removeFromLeft(ctrlThirds);
    auto modDepthBounds = upperCtrls.removeFromLeft(ctrlThirds);
    auto modSpeedBounds = upperCtrls;

    auto modTypeBounds = bounds.removeFromRight(ctrlThirds);

    auto widthVals = bounds.getWidth() / 3;
    auto prevValBounds = bounds.removeFromLeft(widthVals);
    auto oscTypeBounds = bounds.removeFromLeft(widthVals);

    m_PitchLabel.setBounds(pitchBounds.removeFromTop(22)); m_Pitch.setBounds(pitchBounds);
    m_ModDepthLabel.setBounds(modDepthBounds.removeFromTop(22)); m_ModDepth.setBounds(modDepthBounds);
    m_ModSpeedLabel.setBounds(modSpeedBounds.removeFromTop(22)); m_ModSpeed.setBounds(modSpeedBounds);
    m_ModTypeLabel.setBounds(modTypeBounds.removeFromTop(22)); m_ModType.setBounds(modTypeBounds);
    m_OscTypeLabel.setBounds(oscTypeBounds.removeFromTop(22)); m_OscType.setBounds(oscTypeBounds);
    
    m_Pitch.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_ModDepth.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_ModSpeed.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_ModType.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
}
