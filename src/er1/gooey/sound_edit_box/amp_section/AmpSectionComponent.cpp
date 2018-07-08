/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "AmpSectionComponent.h"

using namespace juce;

AmpSectionComponent::AmpSectionComponent()
    : m_Decay("Decay")
    , m_Level("Level")
    , m_Pan("Pan")
    , m_LowBoost("Low Boost")
{
    m_Decay.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_Level.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_Pan.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_LowBoost.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    addAndMakeVisible(m_Decay);
    addAndMakeVisible(m_Level);
    addAndMakeVisible(m_Pan);
    addAndMakeVisible(m_LowBoost);
}

AmpSectionComponent::~AmpSectionComponent() {}

void AmpSectionComponent::paint (Graphics& g)
{
    auto header = getLocalBounds().removeFromTop(22);

    g.setColour(Colours::black);
    g.fillRect(header);

    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.drawFittedText("AMP", header, juce::Justification::centred, 1);
}

void AmpSectionComponent::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(22);
    bounds = bounds.reduced(2);

    auto upperCtrls = bounds.removeFromTop(bounds.getHeight() / 2);

    auto decayBounds = upperCtrls.removeFromLeft(upperCtrls.getWidth() / 2);
    auto levelBounds = upperCtrls;

    auto panBounds = bounds.removeFromLeft(bounds.getWidth() / 2);
    auto boostBounds = bounds;

    m_Decay.setBounds(decayBounds);
    m_Level.setBounds(levelBounds);
    m_Pan.setBounds(panBounds);
    m_LowBoost.setBounds(boostBounds);
    
    m_Decay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_Level.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_Pan.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_LowBoost.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
}
