//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "../look_and_feel/ER1Colours.h"

static int makeFlags()
{
    return juce::FileBrowserComponent::canSelectFiles || juce::FileBrowserComponent::openMode;
}

PatchManager::PatchManager(const juce::File& startingDir, const std::string& name, const juce::WildcardFileFilter& filter)
    : m_WildcardFilter(filter)
    , m_DirectoryThread(name)
    , m_ChangeDir("Change Dir")
    , m_New("New")
    , m_Delete("Delete")
{
    m_FileList.setDirectory(startingDir, true, true);
    m_DirectoryThread.startThread();

    m_FileTree.setRowHeight(14);
    m_FileTree.addListener(this);
    m_FileTree.setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, juce::Colours::red);
    m_FileTree.setColour(juce::ListBox::ColourIds::backgroundColourId, ER1Colours::lcdRed);


    addAndMakeVisible(m_FileTree);
    addAndMakeVisible(m_New);
    addAndMakeVisible(m_Delete);
    addAndMakeVisible(m_ChangeDir);

    m_ChangeDir.addListener(this);
    m_New.addListener(this);
    m_Delete.addListener(this);
}

void PatchManager::paint(juce::Graphics& g)
{
    g.setColour(ER1Colours::lcdRed);
    g.fillAll();

    auto bounds = getLocalBounds();
    bounds.removeFromBottom(15);
    g.setColour(juce::Colours::red.darker());
    g.drawRect(bounds.reduced(1), 1);
}

void PatchManager::resized()
{
    auto bounds = getLocalBounds();
    auto buttonRow = bounds.removeFromBottom(15);
    m_FileTree.setBounds(bounds.reduced(2));

    buttonRow.removeFromLeft(1);
    m_ChangeDir.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4) * 0.417));
    buttonRow.removeFromLeft(2);
    m_New.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4) * 0.25));
    buttonRow.removeFromLeft(2);
    m_Delete.setBounds(buttonRow.removeFromLeft(((bounds.getWidth() - 4) * 0.333) - 1));
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
        m_FileList.setDirectory(f, true, true);
    }
}

void PatchManager::buttonClicked(juce::Button* btn)
{
    if (btn == &m_ChangeDir)
    {
        std::cout << "Change dir" << std::endl;
    }

    else if (btn == &m_New)
    {
        std::cout << "New" << std::endl;
    }

    else if (btn == &m_Delete)
    {
        std::cout << "Delete" << std::endl;
    }
}
