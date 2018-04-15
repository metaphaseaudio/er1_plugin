/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../guts/PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
ER1AudioProcessorEditor::ER1AudioProcessorEditor (ER1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

	addAndMakeVisible(m_RedBoxComponent);
    addAndMakeVisible(m_AmpSectionComponent);
    addAndMakeVisible(m_TransportComponent);
}

ER1AudioProcessorEditor::~ER1AudioProcessorEditor()
{
}

//==============================================================================
void ER1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	
	const auto bezel = getLocalBounds().reduced(5);
	g.setColour(juce::Colours::silver);
	g.fillRect(bezel);
}

void ER1AudioProcessorEditor::resized()
{
    // horizontal slicing
    auto internalBounds = getLocalBounds().reduced(15);
    auto titleBar = internalBounds.removeFromTop(50);
    internalBounds.removeFromTop(5);  // margin
    auto ctrls = internalBounds.removeFromTop(400);
    internalBounds.removeFromTop(5);  // margin
    auto sequencer = internalBounds;

    auto leftBox = ctrls.removeFromLeft(393);
    ctrls.removeFromLeft(5);  // margin

    // Oscillator and Amp ctrls
    auto oscandamp = ctrls.removeFromTop(200);
    auto osc = oscandamp.removeFromLeft(300);
    auto amp = oscandamp;

    m_AmpSectionComponent.setBounds(amp);


    // Left-box
    m_RedBoxComponent.setBounds(leftBox.removeFromTop(300));
    leftBox.removeFromTop(5);
    m_TransportComponent.setBounds(leftBox);
}
