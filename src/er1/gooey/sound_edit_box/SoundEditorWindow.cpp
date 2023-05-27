//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"

SoundEditorWindow::SoundEditorWindow(GlobalOptions& opts, const ER1SoundPatch::Ptr& sound)
    : m_OscSection(opts, sound->osc)
    , m_AmpSection(opts, sound->amp)
    , m_DelaySection(opts, sound->delay)
{
    addAndMakeVisible(&m_OscSection);
    addAndMakeVisible(&m_AmpSection);
    addAndMakeVisible(&m_DelaySection);

    m_OscSection.setInterceptsMouseClicks(false, true);
    m_AmpSection.setInterceptsMouseClicks(false, true);
    m_DelaySection.setInterceptsMouseClicks(false, true);
}

void SoundEditorWindow::resized()
{
    m_OscSection.setBounds(getLocalBounds());
    m_AmpSection.setBounds(getLocalBounds());
    m_DelaySection.setBounds(getLocalBounds());
}

void SoundEditorWindow::changeListenerCallback(juce::ChangeBroadcaster*)
{
    repaint();
}
