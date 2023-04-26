/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../guts/ER1AudioProcessor.h"
#include "ER1AudioProcessorEditor.h"

#include <memory>
#include "BGImage.h"
#include "Images.h"
#include "look_and_feel/StandardShapes.h"


using namespace juce;

//==============================================================================
ER1AudioProcessorEditor::ER1AudioProcessorEditor(ER1AudioProcessor& p)
    : AudioProcessorEditor(&p)
    , processor(p)
{
    processor.addChangeListener(this);
    setLookAndFeel(&m_LAF);
    juce::LookAndFeel::setDefaultLookAndFeel(&m_LAF);

    p_VoiceSelector = std::make_unique<VoiceSelector>(p.getMidiManager(), p.getSynth().getVoices());
    p_GlobalCtrls = std::make_unique<GlobalCtrls>(p.getMidiManager(), p);

    for (int i = 0; i < meta::ER1::ER1_SOUND_COUNT; i++)
    {
        m_SoundEditorWindows.emplace_back(new SoundEditorWindow(p.getOptions(), p.getSound(i)));
        auto* window = m_SoundEditorWindows.at(i).get();
        p.getMidiManager().addChangeListener(window);
        addChildComponent(window);
    }

    addAndMakeVisible(p_VoiceSelector.get());
    addAndMakeVisible(m_Divider);
    addAndMakeVisible(p_GlobalCtrls.get());
    getChildComponent(0)->setVisible(true);
    p_GlobalCtrls->addChangeListener(this);
    p_VoiceSelector->addChangeListener(this);

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
    for (auto& window : m_SoundEditorWindows)
        { window->setBounds(getLocalBounds()); }

    p_GlobalCtrls->setBounds(getLocalBounds());
    p_VoiceSelector->setBounds(getLocalBounds());
}

void ER1AudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == p_VoiceSelector.get())
    {
        for (auto& editor : m_SoundEditorWindows) { editor->setVisible(false); }
        const auto selected = p_VoiceSelector->getSelected();
        if (selected >= meta::ER1::ER1_SOUND_COUNT) { return; }

        p_GlobalCtrls->setVoice(processor.getSynth().getVoices()[selected]->getControlBlock());
        m_SoundEditorWindows[selected]->setVisible(true);
        processor.triggerVoice(selected);
    }

    if (source == p_GlobalCtrls.get())
    {
        processor.setBankPresetFolder(p_GlobalCtrls->getCurrentBankFolder());
        processor.setSoundPresetFolder(p_GlobalCtrls->getCurrentSoundFolder());
        repaint();
    }

    if (source == &processor)
    {
        p_GlobalCtrls->setCurrentBankFolder(processor.getBankPresetFolder());
        p_GlobalCtrls->setCurrentSoundFolder(processor.getSoundPresetFolder());
        p_GlobalCtrls->setBankName(processor.getPatchName());
    }
}
