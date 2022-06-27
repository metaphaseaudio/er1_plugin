//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "../look_and_feel/ER1Colours.h"


static std::string stripStar(const std::string& x)
{
    auto rv = x;
    rv.erase(std::remove(rv.begin(), rv.end(), '*'), rv.end());
    return rv;
}


PatchManager::PatchManager(Serializeable* target, const juce::File& startingDir, const std::string& name,  const std::string& customSuffix)
    : p_Target(target)
    , m_Suffix(stripStar(customSuffix))
    , m_WildcardFilter{"*.json;" + customSuffix +";", "*", "Bank Patch Filter"}
    , m_DirectoryThread(name)
    , m_ChangeDir("Change Dir")
    , m_New("New")
    , m_Delete("Delete")
{
    m_DirList.setDirectory(startingDir, true, true);
    m_DirectoryThread.startThread();

    m_FileListComponent.setRowHeight(14);
    m_FileListComponent.addListener(this);
    m_FileListComponent.setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, juce::Colours::red);
    m_FileListComponent.setColour(juce::ListBox::ColourIds::backgroundColourId, ER1Colours::lcdRed);

    addAndMakeVisible(m_FileListComponent);
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
    bounds.removeFromBottom(12);
    g.setColour(juce::Colours::red.darker());
    g.drawRect(bounds.reduced(1), 1);
}

void PatchManager::resized()
{
    auto bounds = getLocalBounds();
    auto buttonRow = bounds.removeFromBottom(12);
    m_FileListComponent.setBounds(bounds.reduced(2));

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
    m_FileListComponent.removeListener(this);
}

void PatchManager::fileDoubleClicked(const juce::File& f)
{
    if (f.isDirectory())
    {
        m_DirList.setDirectory(f, true, true);
    }
}

void PatchManager::buttonClicked(juce::Button* btn)
{
    if (btn == &m_ChangeDir)
    {
        m_FileChooser = std::make_unique<juce::FileChooser>("Change Directory", m_DirList.getDirectory());
        m_FileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
            [this] (const juce::FileChooser& chooser) {
                const auto& result = chooser.getResult();
                if (result.exists() && result.isDirectory())
                    { m_DirList.setDirectory(result, true, true); }
            }
        );
    }

    else if (btn == &m_New)
    {
        const auto string_data = p_Target->toJson().dump(4);
        auto new_file = m_DirList.getDirectory().getChildFile("new_patch" + m_Suffix);
        int copy = 0;
        while (new_file.exists())
        {
            copy++;
            new_file = m_DirList.getDirectory().getChildFile("new_patch_" + juce::String(copy) + m_Suffix);
        }

        new_file.create();
        auto stream = new_file.createOutputStream();
        stream->writeString(string_data);
        stream->flush();
        stream.reset(nullptr);

        m_DirList.refresh();

    }

    else if (btn == &m_Delete)
    {
        std::cout << "Delete" << std::endl;
    }
}
