//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "../look_and_feel/ER1Colours.h"

PatchManager::PatchManager()
{
    const auto homeDir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory);
    m_ImageList.setDirectory(homeDir, true, true);
    m_DirectoryThread.startThread();

    m_FileTree.setRowHeight(15);
    m_FileTree.addListener(this);
    addAndMakeVisible(m_FileTree);
    m_FileTree.setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, juce::Colours::red);
    m_FileTree.setColour(juce::ListBox::ColourIds::backgroundColourId, ER1Colours::lcdRed);
}

void PatchManager::paint(juce::Graphics& g)
{}

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
