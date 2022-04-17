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

OscSectionComponent::OscSectionComponent(OscParams& params)
    : m_Pitch(*params.pitch), m_PitchLabel("Pitch Label", "Pitch")
    , m_ModDepth(*params.modDepth), m_ModDepthLabel("Mod Depth Label", "Mod Depth")
    , m_ModSpeed(*params.modSpeed, 8000), m_ModSpeedLabel("Mod Speed Label", "Mod Speed")
    , m_ModType(*params.modType), m_ModTypeLabel("Mod Type Label", "Mod Type")
    , m_OscType(*params.oscType), m_OscTypeLabel("Osc Type Label", "Osc Type")
{
    m_PitchLabel.setJustificationType(juce::Justification::centred);
    m_ModSpeedLabel.setJustificationType(juce::Justification::centred);
    m_ModDepthLabel.setJustificationType(juce::Justification::centred);

    m_Pitch.setSkewFactor(0.2);
    addAndMakeVisible(m_Pitch);    addAndMakeVisible(m_PitchLabel);
    m_ModSpeed.setSkewFactor(0.2);
    addAndMakeVisible(m_ModSpeed); addAndMakeVisible(m_ModSpeedLabel);
    addAndMakeVisible(m_ModDepth); addAndMakeVisible(m_ModDepthLabel);
    addAndMakeVisible(m_ModType);  addAndMakeVisible(m_ModTypeLabel);
    addAndMakeVisible(m_OscType);  addAndMakeVisible(m_OscTypeLabel);
}


void OscSectionComponent::paint (Graphics& g)
{
    auto header = getLocalBounds().removeFromTop(22);

    g.setColour(Colours::black);
    g.fillRect(header);

    g.setFont(g.getCurrentFont().boldened());
    g.setColour(ER1Colours::defaultForeground);
    g.drawFittedText("OSCILLATOR", header, juce::Justification::centred, 1);
}

void OscSectionComponent::resized()
{
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    bounds.removeFromTop(labelHeight);
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
