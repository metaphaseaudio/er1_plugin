/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "AmpSectionComponent.h"
#include "../../look_and_feel/StandardShapes.h"
#include "../../look_and_feel/ER1Colours.h"

using namespace juce;

AmpSectionComponent::AmpSectionComponent(AmpParams& params)
    : m_Header("AMP")
    , m_Decay(params.decay, 0.5f), m_DecayLabel("Decay Label", "Decay")
    , m_Level(params.level, 0.6f), m_LevelLabel("Level Label", "Level")
    , m_Pan(params.pan, 0.0f), m_PanLabel("Pan Label", "Pan")
    , m_LowBoost(params.lowBoost, 0.0f), m_LowBoostLabel("Low Boost Label", "Low Boost")
{

    m_DecayLabel.setJustificationType(juce::Justification::centred);
    m_LevelLabel.setJustificationType(juce::Justification::centred);
    m_PanLabel.setJustificationType(juce::Justification::centred);
    m_LowBoostLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Header);
    addAndMakeVisible(m_Decay);    addAndMakeVisible(m_DecayLabel);
    addAndMakeVisible(m_Level);    addAndMakeVisible(m_LevelLabel);
    addAndMakeVisible(m_Pan);      addAndMakeVisible(m_PanLabel);
    addAndMakeVisible(m_LowBoost); addAndMakeVisible(m_LowBoostLabel);
}


void AmpSectionComponent::resized()
{
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    m_Header.setBounds(bounds.removeFromTop(labelHeight));
    bounds = bounds.reduced(2);

    auto ctrlBounds = StandardShapes::largeDial;
    auto labelBounds = bounds.removeFromTop(labelHeight).removeFromLeft(ctrlBounds.getWidth());
    ctrlBounds.setPosition(bounds.getBottomLeft().x, labelBounds.getBottom());

    m_DecayLabel.setBounds(labelBounds); m_Decay.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_LevelLabel.setBounds(labelBounds); m_Level.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_PanLabel.setBounds(labelBounds); m_Pan.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);

    m_LowBoostLabel.setBounds(labelBounds); m_LowBoost.setBounds(ctrlBounds);
    ctrlBounds.setPosition(ctrlBounds.getRight() + margin, labelBounds.getBottom());
    labelBounds.setPosition(labelBounds.getRight() + margin, labelBounds.getTopRight().y);
}
