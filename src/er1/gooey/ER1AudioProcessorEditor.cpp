/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../guts/ER1AudioProcessor.h"
#include "ER1AudioProcessorEditor.h"

using namespace juce;

//==============================================================================
ER1AudioProcessorEditor::ER1AudioProcessorEditor (ER1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(900, 600);

	addAndMakeVisible(m_RedBoxComponent);
    addAndMakeVisible(m_OscSectionComponent);
    addAndMakeVisible(m_AmpOscDiv);
    addAndMakeVisible(m_AmpSectionComponent);
    addAndMakeVisible(m_TransportComponent);
    addAndMakeVisible(m_Sequencer);
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

    m_Sequencer.setBounds(internalBounds);

    auto leftBox = ctrls.removeFromLeft(393);
    ctrls.removeFromLeft(5);  // margin

    // Oscillator and Amp ctrls
    auto oscandamp = ctrls.removeFromTop(200);
    auto osc = oscandamp.removeFromLeft(300);
    m_AmpOscDiv.setBounds(oscandamp.removeFromLeft(7));
    auto amp = oscandamp;

    m_OscSectionComponent.setBounds(osc);
    m_AmpSectionComponent.setBounds(amp);

    // Left-box
    m_RedBoxComponent.setBounds(leftBox.removeFromTop(300));
    leftBox.removeFromTop(5);
    m_TransportComponent.setBounds(leftBox);
}
