//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "../look_and_feel/ER1Colours.h"
#include "../fonts/FontLCD.h"


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
    , m_ChangeDir("Dir")
    , m_New("New")
    , m_Save("Save")
    , m_Delete("Delete")
{
    m_DirList.setDirectory(startingDir, true, true);
    m_DirectoryThread.startThread();

    m_Editor.setColour(juce::TextEditor::ColourIds::backgroundColourId, m_FileListComponent.findColour(juce::DirectoryContentsDisplayComponent::ColourIds::highlightColourId));
    m_Editor.setColour(juce::TextEditor::ColourIds::textColourId, juce::Colours::white);
    m_Editor.setFont(FontLCD::defaultFont().withPointHeight(11));
    m_Editor.setBorder(juce::BorderSize<int>(0));
    m_Editor.addListener(this);

    m_FileListComponent.setRowHeight(14);
    m_FileListComponent.addListener(this);
    m_FileListComponent.setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, juce::Colours::red);
    m_FileListComponent.setColour(juce::ListBox::ColourIds::backgroundColourId, ER1Colours::lcdRed);


    addAndMakeVisible(m_FileListComponent);
    addAndMakeVisible(m_New);
    addAndMakeVisible(m_Save);
    addAndMakeVisible(m_Delete);
    addAndMakeVisible(m_ChangeDir);
    addChildComponent(m_Editor);

    m_ChangeDir.addListener(this);
    m_New.addListener(this);
    m_Save.addListener(this);
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
    m_ChangeDir.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4) * 0.20));
    buttonRow.removeFromLeft(2);
    m_New.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4) * 0.25));
    buttonRow.removeFromLeft(2);
    m_Save.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4) * 0.25));
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
        { m_DirList.setDirectory(f, true, true); }
    else
        { startRenameSelected(); }
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
        auto new_file = m_DirList.getDirectory().getChildFile("new_patch" + m_Suffix);
        int copy = 0;
        while (new_file.exists())
        {
            copy++;
            new_file = m_DirList.getDirectory().getChildFile("new_patch_" + juce::String(copy) + m_Suffix);
        }

        new_file.create();
        saveStateToFile(new_file);
        refreshAndSetSelected(new_file);
        startRenameSelected();
    }

    else if (btn == &m_Save)
    {
        const auto selected_i = m_FileListComponent.getSelectedRows()[0];
        const auto selected_file = m_DirList.getFile(selected_i);
        saveStateToFile(selected_file);
    }

    else if (btn == &m_Delete)
    {
        auto f = m_DirList.getFile(m_FileListComponent.getSelectedRows()[0]);
        f.deleteFile();
        m_DirList.refresh();
    }
}

void PatchManager::startRenameSelected()
{
    const auto selected_i = m_FileListComponent.getSelectedRows()[0];
    auto selected_point = m_FileListComponent.getRowPosition(selected_i, false);
    selected_point.removeFromLeft(selected_point.getHeight());
    selected_point.removeFromTop(2);
    const auto selected_file = m_DirList.getFile(selected_i);
    const auto filename = selected_file.getFileName();

    m_Editor.setBounds(selected_point);
    m_Editor.setVisible(true);
    m_Editor.setText(filename);
    m_Editor.setHighlightedRegion(juce::Range<int>(0, filename.length()));
    m_Editor.grabKeyboardFocus();
}

void PatchManager::textEditorReturnKeyPressed(juce::TextEditor& editor)
{
    m_Editor.giveAwayKeyboardFocus();
    m_Editor.setVisible(false);
}

void PatchManager::textEditorFocusLost(juce::TextEditor& editor)
{
    auto newName = m_Editor.getText();
    const auto selected_i = m_FileListComponent.getSelectedRows()[0];
    auto file = m_DirList.getFile(selected_i);
    auto newFile = file.getParentDirectory().getChildFile(newName).withFileExtension(m_Suffix);
    file.moveFileTo(newFile);
    refreshAndSetSelected(newFile);
}

void PatchManager::refreshAndSetSelected(juce::File& f)
{
    m_DirList.refresh();

    while (m_DirList.isStillLoading()) {};

    m_FileListComponent.updateContent();
    m_FileListComponent.setSelectedFile(f);
    auto rows = m_FileListComponent.getSelectedRows();
    m_FileListComponent.scrollToEnsureRowIsOnscreen(rows[0]);
    m_FileListComponent.repaint();
}

void PatchManager::selectionChanged()
{
    const auto selected_i = m_FileListComponent.getSelectedRows()[0];
    const auto file = m_DirList.getFile(selected_i);
    if (!file.exists()) { return; }
    const auto reader = file.createInputStream();

    try
    {
        auto j = nlohmann::json::parse(reader->readEntireStreamAsString().toStdString());
        p_Target->fromJson(j);
        sendChangeMessage();
    }
    catch (nlohmann::json::exception& err)
        { std::cout << err.what() << std::endl; }

}

void PatchManager::saveStateToFile(const juce::File& f)
{
    const auto string_data = p_Target->toJson().dump(4);
    auto stream = f.createOutputStream();
    stream->setPosition(0);
    stream->truncate();
    stream->writeString(string_data);
    stream->flush();
    stream.reset(nullptr);
}
