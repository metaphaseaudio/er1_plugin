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
    processor.addChangeListener(this);
    setLookAndFeel(&m_LAF);
    juce::LookAndFeel::setDefaultLookAndFeel(&m_LAF);

    for (int i = 0; i < meta::ER1::ER1_SOUND_COUNT; i++)
    {
        m_SoundEditorWindows.emplace_back(new SoundEditorWindow(p.getOptions(), p.getSound(i)));
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

    setSize(960, 540);
}

ER1AudioProcessorEditor::~ER1AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
    processor.removeChangeListener(this);
}

//==============================================================================
void ER1AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	const auto bezel = getLocalBounds().reduced(3);
	g.setColour(juce::Colours::silver);
	g.fillRect(bezel);
    g.reduceClipRegion(bezel);

    auto file = juce::File(R"(C:\Users\Matt\code\rendered_ui_images\0001.png)");
    auto img = std::make_unique<juce::Image>(juce::ImageFileFormat::loadFrom(file));
    Image bg = ImageCache::getFromMemory(Images::bg_2_png, Images::bg_2_pngSize);
    g.drawImage(*img, getLocalBounds().toFloat());
}

void ER1AudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(7);
    auto internalBounds = bounds.removeFromTop(245);

    for (auto& window : m_SoundEditorWindows)
        { window->setBounds(getLocalBounds()); }

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

        m_GlobalCtrls.setVoice(processor.getSynth().getVoices()[selected]->getControlBlock());
        m_SoundEditorWindows[selected]->setVisible(true);
        processor.triggerVoice(selected);
    }

    if (source == &m_GlobalCtrls)
    {
        processor.setBankPresetFolder(m_GlobalCtrls.getCurrentBankFolder());
        processor.setSoundPresetFolder(m_GlobalCtrls.getCurrentSoundFolder());
        repaint();
    }

    if (source == &processor)
    {
        m_GlobalCtrls.setCurrentBankFolder(processor.getBankPresetFolder());
        m_GlobalCtrls.setCurrentSoundFolder(processor.getSoundPresetFolder());
        m_GlobalCtrls.setBankName(processor.getPatchName());
    }
}
