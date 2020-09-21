//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"
#include "../fonts/FontLCD.h"

SoundEditorWindow::SoundEditorWindow()
{
    addAndMakeVisible(&m_PadGrid);
    addAndMakeVisible(&m_PatchSelector);
    addAndMakeVisible(&m_VoiceSetup);
    addAndMakeVisible(&m_AmpSection);
    addAndMakeVisible(&m_OscSection);
    m_PadGrid.addChangeListener(this);
}

void SoundEditorWindow::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    auto upper_percentage = 0.3f;
    auto upper_bounds = bounds.removeFromTop(80);// (bounds.getHeight() * upper_percentage);
    m_PatchSelector.setBounds(upper_bounds.removeFromLeft(150));//(upper_bounds.getHeight()).reduced(2));
    upper_bounds.removeFromLeft(5);
    m_VoiceSetup.setBounds(upper_bounds);

    bounds.removeFromTop(5);
    m_OscSection.setBounds(bounds.removeFromTop(160));
    m_AmpSection.setBounds(bounds);
}

void SoundEditorWindow::changeListenerCallback(juce::ChangeBroadcaster* source)
{

}

void SoundEditorWindow::setVoice(meta::ER1::Voice* voice)
{

}
