/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../guts/ER1AudioProcessor.h"
#include "ER1AudioProcessorEditor.h"
#include "BGImage.h"
#include "Images.h"
#include "look_and_feel/StandardShapes.h"


using namespace juce;

//==============================================================================
ER1AudioProcessorEditor::ER1AudioProcessorEditor(ER1AudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
    , m_VoiceSelector(p.getMidiManager(), p.getSynth().getVoices())
    , m_GlobalCtrls(p.getMidiManager(), p)
{
    setLookAndFeel(&m_LAF);

    for (int i = 0; i < meta::ER1::ER1_SOUND_COUNT; i++)
    {
        m_SoundEditorWindows.emplace_back(new SoundEditorWindow(p.getSound(i)));
        auto* window = m_SoundEditorWindows.at(i).get();
        p.getMidiManager().addChangeListener(window);
        addChildComponent(window);
    }

    addAndMakeVisible(m_VoiceSelector);
    addAndMakeVisible(m_Divider);
    addAndMakeVisible((m_GlobalCtrls));
    getChildComponent(0)->setVisible(true);
    m_GlobalCtrls.addChangeListener(this);
    m_VoiceSelector.addChangeListener(this);
    setSize(600, 380);
}

ER1AudioProcessorEditor::~ER1AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void ER1AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	const auto bezel = getLocalBounds().reduced(3);
	g.setColour(juce::Colours::silver);
	g.fillRect(bezel);
    g.reduceClipRegion(bezel);

    Image bg = ImageCache::getFromMemory(Images::bg_png, Images::bg_pngSize);
    g.drawImage(bg, getLocalBounds().toFloat());
}

void ER1AudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(7);

    auto internalBounds = bounds.removeFromTop(245);

    for (auto& window : m_SoundEditorWindows)
        { window->setBounds(internalBounds); }

    auto upper_bounds = internalBounds.removeFromTop(120);
    m_GlobalCtrls.setBounds(upper_bounds.removeFromLeft(220));

    bounds.removeFromTop(5);
    m_Divider.setBounds(bounds.removeFromTop(5));
    m_VoiceSelector.setBounds(bounds);
}

void ER1AudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_VoiceSelector)
    {
        for (auto& editor : m_SoundEditorWindows) { editor->setVisible(false); }
        const auto selected = m_VoiceSelector.getSelected();

        if (selected >= meta::ER1::ER1_SOUND_COUNT) { return; }
        m_SoundEditorWindows[m_VoiceSelector.getSelected()]->setVisible(true);
        processor.triggerVoice(selected);
    }

    if (source == &m_GlobalCtrls)
        { repaint(); }
}
