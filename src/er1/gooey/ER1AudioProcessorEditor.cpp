/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../guts/ER1AudioProcessor.h"
#include "ER1AudioProcessorEditor.h"
#include "BGImage.h"


using namespace juce;

//==============================================================================
ER1AudioProcessorEditor::ER1AudioProcessorEditor(ER1AudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
{
    setLookAndFeel(&m_LAF);
    setSize(600, 380);

    for (int i = 0; i < ER1AudioProcessor::ER1_SOUND_COUNT; i++)
    {
        m_SoundEditorWindows.emplace_back(new SoundEditorWindow(p.getSound(i)));
        auto* window = m_SoundEditorWindows.at(i).get();
        window->setBounds(getLocalBounds().reduced(5));
        addChildComponent(window);
    }

    addAndMakeVisible(m_PatchSelector);
    addAndMakeVisible(m_Divider);
    getChildComponent(0)->setVisible(true);
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

    Image bg = ImageCache::getFromMemory(BGImage::brushed_steel_png, BGImage::brushed_steel_pngSize);
    g.drawImage(bg, bezel.toFloat());
}

void ER1AudioProcessorEditor::resized()
{
    // horizontal slicing
    auto bounds = getLocalBounds().reduced(5);

    const auto internalBounds = bounds.removeFromTop(245);

    for (auto& window : m_SoundEditorWindows)
        { window->setBounds(internalBounds); }

    bounds.removeFromTop(5);
    m_Divider.setBounds(bounds.removeFromTop(5));
    m_PatchSelector.setBounds(bounds);
}
