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
    : m_Depth(params.depth), m_DepthLabel("Depth Label", "Depth")
    , m_Time(params.time), m_TimeLabel("Time Label", "Time")
    , m_Sync(params.sync), m_SyncLabel("Sync Label", "Tempo\nSync")
{

    m_DepthLabel.setJustificationType(juce::Justification::centred);
    m_TimeLabel.setJustificationType(juce::Justification::centred);
    m_SyncLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Depth); addAndMakeVisible(m_DepthLabel);
    addAndMakeVisible(m_Time); addAndMakeVisible(m_TimeLabel);
    addAndMakeVisible(m_Sync); addAndMakeVisible(m_SyncLabel);
}

DelaySectionComponent::~DelaySectionComponent() = default;

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
    bounds.removeFromTop(labelHeight); // Give room for the section label
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
