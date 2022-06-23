//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "../widgets/LCDText.h"

PatchManager::PatchManager()
{
    const auto homeDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory);
    m_ImageList.setDirectory(homeDir, true, true);
    m_DirectoryThread.startThread();

    m_FileTree.setRowHeight(18);
    m_FileTree.addListener(this);
    addAndMakeVisible(m_FileTree);
}

void PatchManager::paint(juce::Graphics& g)
{
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::lcdColour));
    g.fillAll();
}

void PatchManager::resized()
{
    m_FileTree.setBounds(getLocalBounds());
}

PatchManager::~PatchManager()
{
    m_DirectoryThread.stopThread(1000);
    m_FileTree.removeListener(this);
}

void PatchManager::fileDoubleClicked(const juce::File& f)
{
    if (f.isDirectory())
    {
        m_ImageList.setDirectory(f, true, true);
    }
}
