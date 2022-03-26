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

DelaySectionComponent::DelaySectionComponent(DelayParams& params)
    : m_Depth(*params.depth), m_DepthLabel("Depth Label", "Depth")
    , m_Time(*params.time), m_TimeLabel("Time Label", "Time")
{

    m_DepthLabel.setJustificationType(juce::Justification::centred);
    m_TimeLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Depth);    addAndMakeVisible(m_DepthLabel);
    addAndMakeVisible(m_Time);    addAndMakeVisible(m_TimeLabel);
}

DelaySectionComponent::~DelaySectionComponent() {}

void DelaySectionComponent::paint (Graphics& g)
{
    auto header = getLocalBounds().removeFromTop(22);

    g.setColour(Colours::black);
    g.fillRect(header);

    g.setFont(g.getCurrentFont().boldened());
    g.setColour(ER1Colours::defaultForeground);
    g.drawFittedText("DELAY", header, juce::Justification::centred, 1);
}

void DelaySectionComponent::resized()
{
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    bounds.removeFromTop(labelHeight);
    bounds = bounds.reduced(2);

    auto ctrlBounds = StandardShapes::largeDial;
    auto labelBounds = bounds.removeFromTop(labelHeight).removeFromLeft(ctrlBounds.getWidth());
    ctrlBounds.setPosition(bounds.getBottomLeft().x, labelBounds.getBottom());

    m_TimeLabel.setBounds(labelBounds); m_Time.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_DepthLabel.setBounds(labelBounds); m_Depth.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);
}
