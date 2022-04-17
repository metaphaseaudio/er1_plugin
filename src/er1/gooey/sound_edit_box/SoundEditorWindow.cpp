//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"

SoundEditorWindow::SoundEditorWindow(ER1Sound::Ptr sound)
    : m_VoiceSetup(dynamic_cast<ER1Sound*>(sound.get())->config)
    , m_OscSection(dynamic_cast<ER1Sound*>(sound.get())->osc)
    , m_AmpSection(dynamic_cast<ER1Sound*>(sound.get())->amp)
    , m_DelaySection(dynamic_cast<ER1Sound*>(sound.get())->delay)
{
    addAndMakeVisible(&m_VoiceSetup);
    addAndMakeVisible(&m_OscSection);
    addAndMakeVisible(&m_AmpSection);
    addAndMakeVisible(&m_DelaySection);
    addAndMakeVisible(&m_Divider);
}

void SoundEditorWindow::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    auto upper_bounds = bounds.removeFromTop(120);
    m_VoiceSetup.setBounds(upper_bounds.removeFromLeft(220));
    upper_bounds.removeFromLeft(5);
    m_OscSection.setBounds(upper_bounds);

    bounds.removeFromTop(5);
    auto secondRow = bounds.removeFromTop(120);
    m_AmpSection.setBounds(secondRow.removeFromLeft(340));
    secondRow.removeFromLeft(5);
    m_DelaySection.setBounds(secondRow);

    bounds.removeFromTop(5);
    m_Divider.setBounds(bounds.removeFromTop(5));
}

void SoundEditorWindow::changeListenerCallback(juce::ChangeBroadcaster* source)
{

}