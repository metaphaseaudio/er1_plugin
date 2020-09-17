/*
  ==============================================================================

    OscSectionComponent.cpp
    Created: 16 Apr 2018 6:04:00pm
    Author:  Matt Zapp

  ==============================================================================
*/

#include "OscSectionComponent.h"
#include "../../look_and_feel/StandardShapes.h"

using namespace juce;

OscSectionComponent::OscSectionComponent()
    : m_Pitch("Pitch"), m_PitchLabel("Pitch Label", "Pitch")
    , m_ModDepth("Mod Depth"), m_ModDepthLabel("Mod Depth Label", "Mod Depth")
    , m_ModSpeed("Mod Speed"), m_ModSpeedLabel("Mod Speed Label", "Mod Speed")
    , m_ModType(), m_ModTypeLabel("Mod Type Label", "Mod Type")
    , m_OscType(), m_OscTypeLabel("Osc Type Label", "Osc Type")
{
    m_Pitch.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_ModSpeed.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    m_ModDepth.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    m_PitchLabel.setJustificationType(juce::Justification::centred);
    m_ModSpeedLabel.setJustificationType(juce::Justification::centred);
    m_ModDepthLabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(m_Pitch);    addAndMakeVisible(m_PitchLabel);
    addAndMakeVisible(m_ModSpeed); addAndMakeVisible(m_ModSpeedLabel);
    addAndMakeVisible(m_ModDepth); addAndMakeVisible(m_ModDepthLabel);
    addAndMakeVisible(m_ModType);  addAndMakeVisible(m_ModTypeLabel);
    addAndMakeVisible(m_OscType);  addAndMakeVisible(m_OscTypeLabel);

    m_OscType.addItem("Sine", SINE);
    m_OscType.addItem("Triangle", TRI);
    m_OscType.addItem("Square", SQUARE);
    m_OscType.setSelectedId(SINE, juce::NotificationType::dontSendNotification);
    m_OscType.addListener(this);

    m_ModType.addItem("Sine", SINE);
    m_ModType.addItem("Triangle", TRI);
    m_ModType.addItem("Square", SQUARE);
    m_ModType.addItem("Random Step", STEP);
    m_ModType.addItem("Random Noise", NOISE);
    m_ModType.addItem("Sweep", SWEEP);
    m_ModType.setSelectedId(SINE, juce::NotificationType::dontSendNotification);
    m_ModType.addListener(this);


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
    const auto margin = 10;

    auto bounds = getLocalBounds();
    bounds.removeFromTop(labelHeight);
    bounds = bounds.reduced(2);

    auto ctrlBounds = StandardShapes::largeDial;
    auto selectorBounds = bounds.removeFromRight(bounds.getWidth() - ((ctrlBounds.getWidth() + margin) * 3));

    selectorBounds.removeFromTop(margin);
    m_OscTypeLabel.setBounds(selectorBounds.removeFromTop(labelHeight)); m_OscType.setBounds(selectorBounds.removeFromTop(labelHeight));
    selectorBounds.removeFromTop(margin);
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

    
    m_Pitch.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_ModDepth.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
    m_ModSpeed.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 22);
}

void OscSectionComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{

}
