//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"

SoundEditorWindow::SoundEditorWindow()
{
    addAndMakeVisible(&m_PadGrid);
    addAndMakeVisible(&m_AmpSection);
    addAndMakeVisible(&m_OscSection);
    m_PadGrid.addChangeListener(this);
}

void SoundEditorWindow::resized()
{
    auto bounds = getLocalBounds().reduced(2);
    auto upper_percentage = 0.4f;
    auto upper_bounds = bounds.removeFromTop(bounds.getHeight() * upper_percentage);
    m_PadGrid.setBounds(upper_bounds.removeFromLeft(upper_bounds.getWidth() * upper_percentage));
    m_AmpSection.setBounds(upper_bounds.reduced(4));
    m_OscSection.setBounds(bounds.reduced(4));
}

void SoundEditorWindow::paint(juce::Graphics& g)
{
    g.fillAll(ER1Colours::defaultBackground);
    auto bounds = getLocalBounds();
    g.drawRect(bounds, 2);
}


void SoundEditorWindow::changeListenerCallback(juce::ChangeBroadcaster* source)
{

}
