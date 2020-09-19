/*
  ==============================================================================

    AmpSectionComponent.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "AmpSectionComponent.h"
#include "../../look_and_feel/StandardShapes.h"

using namespace juce;

AmpSectionComponent::AmpSectionComponent()
    : m_Decay("Decay"), m_DecayLabel("Decay Label", "Decay")
    , m_Level("Level"), m_LevelLabel("Level Label", "Level")
    , m_Pan("Pan"), m_PanLabel("Pan Label", "Pan")
    , m_LowBoost("Low Boost"), m_LowBoostLabel("Low Boost Label", "Low Boost")
{
    m_Decay.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_Level.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_Pan.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_LowBoost.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    m_Decay.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_Level.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_Pan.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_LowBoost.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);

    m_DecayLabel.setJustificationType(juce::Justification::centred);
    m_LevelLabel.setJustificationType(juce::Justification::centred);
    m_PanLabel.setJustificationType(juce::Justification::centred);
    m_LowBoostLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Decay);    addAndMakeVisible(m_DecayLabel);
    addAndMakeVisible(m_Level);    addAndMakeVisible(m_LevelLabel);
    addAndMakeVisible(m_Pan);      addAndMakeVisible(m_PanLabel);
    addAndMakeVisible(m_LowBoost); addAndMakeVisible(m_LowBoostLabel);

    m_Pan.setRange(-1.0, 1.0);  m_Pan.setValue(0.0);
    m_Level.setRange(0.0, 1.0); m_Level.setValue(1.0);
    m_Decay.setRange(0.0, 1.0); m_Decay.setValue(0.5);
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
    const auto labelHeight = 22;
    const auto margin = 10;

    auto bounds = getLocalBounds();
    bounds.removeFromTop(labelHeight);
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

void AmpSectionComponent::setVoice(meta::ER1::Voice* voice)
{

}
