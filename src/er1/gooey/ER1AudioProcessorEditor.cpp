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
    , m_Tabs(juce::TabbedButtonBar::Orientation::TabsAtTop)
    , m_Bank(std::array<std::string, 4>({"a", "b", "c", "d"}), meta::Orientation::HORIZ)
    , m_Pads(p.getMidiState())
{
    setLookAndFeel(&m_LAF);
    setSize(500, 600);
    addAndMakeVisible(m_Tabs);
    addAndMakeVisible(m_Bank);
    m_Tabs.addTab("Sounds", juce::Colours::darkgrey, &m_SoundEditorWindow, false);
    m_Tabs.addTab("Pads", juce::Colours::darkgrey, &m_Pads, false);
}

ER1AudioProcessorEditor::~ER1AudioProcessorEditor() {}

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
    auto internalBounds = getLocalBounds().reduced(15);

    internalBounds.removeFromTop(5);
    auto btmCtrls = internalBounds.removeFromBottom(50);
    const auto bankBounds = btmCtrls.removeFromRight(int(jmin<float>(getWidth()/2.0f, 200)));
    const auto transportBounds = btmCtrls.removeFromRight(15);
    m_Bank.setBounds(bankBounds);
    internalBounds.removeFromBottom(5);
    m_Tabs.setBounds(internalBounds);
}

void ER1AudioProcessorEditor::changeListenerCallback(ChangeBroadcaster *source)
{
    if (source == &m_Bank)
        { std::cout << m_Bank.getSelection() << std::endl; }
}
