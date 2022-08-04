//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"

SoundEditorWindow::SoundEditorWindow(GlobalOptions& opts, ER1ControlBlock::Ptr sound)
    : m_VoiceSetup(sound->config)
    , m_OscSection(opts, sound->osc)
    , m_AmpSection(opts, sound->amp)
    , m_DelaySection(opts, sound->delay)
{
    addAndMakeVisible(&m_VoiceSetup);
    addAndMakeVisible(&m_OscSection);
    addAndMakeVisible(&m_AmpSection);
    addAndMakeVisible(&m_DelaySection);
}

void SoundEditorWindow::resized()
{
    auto bounds = getLocalBounds();
    auto upper_bounds = bounds.removeFromTop(120);
    m_VoiceSetup.setBounds(upper_bounds.removeFromLeft(220));
    upper_bounds.removeFromLeft(5);
    m_OscSection.setBounds(upper_bounds);

    bounds.removeFromTop(5);
    auto secondRow = bounds.removeFromTop(120);
    m_AmpSection.setBounds(secondRow.removeFromLeft(340));
    secondRow.removeFromLeft(5);
    m_DelaySection.setBounds(secondRow);
}

void SoundEditorWindow::changeListenerCallback(juce::ChangeBroadcaster*)
{
    repaint();
}
