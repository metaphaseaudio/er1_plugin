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
ER1AudioProcessorEditor::ER1AudioProcessorEditor(ER1AudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , m_VoiceSelector(2, 50)
{
    setLookAndFeel(&m_LAF);
    setSize(360, 450);

    for (int i = 0; i < ER1AudioProcessor::ER1_SOUND_COUNT; i++)
    {
        m_SoundEditorWindows.emplace_back(new SoundEditorWindow(p.getSound(i)));
        auto* window = m_SoundEditorWindows.at(i).get();
        window->setBounds(getLocalBounds().reduced(5));
        addChildComponent(window);
    }

    addAndMakeVisible(m_VoiceSelector);
    getChildComponent(0)->setVisible(true);
    m_VoiceSelector.setText("01");
}

ER1AudioProcessorEditor::~ER1AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void ER1AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	const auto bezel = getLocalBounds().reduced(5);
	g.setColour(juce::Colours::silver);
	g.fillRect(bezel);
}

void ER1AudioProcessorEditor::resized()
{
    // horizontal slicing
    auto internalBounds = getLocalBounds().reduced(5);
    for (auto& window : m_SoundEditorWindows)
        { window->setBounds(internalBounds); }
    auto top = internalBounds.removeFromTop(80);
    m_VoiceSelector.setBounds(top.removeFromLeft(100).reduced(3));
}
