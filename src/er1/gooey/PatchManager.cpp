//
// Created by Mattb on 6/23/2022.
//

#include "PatchManager.h"
#include "look_and_feel/ER1Colours.h"
#include "fonts/FontLCD.h"
#include "widgets/LCDText.h"


static std::string stripStar(const std::string& x)
{
    auto rv = x;
    rv.erase(std::remove(rv.begin(), rv.end(), '*'), rv.end());
    return rv;
}


PatchManager::PatchManager(Patch* target, const juce::File& startingDir, const std::string& name,  const std::string& customSuffix)
    : p_Target(nullptr)
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

    m_FileListComponent.setRowHeight(18);
    m_FileListComponent.addListener(this);
    m_FileListComponent.setColour(juce::DirectoryContentsDisplayComponent::ColourIds::textColourId, getLookAndFeel().findColour(LCDText::ColourIds::textColour));
    m_FileListComponent.setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);

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

    changeTarget(target);
}

void PatchManager::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();
    bounds.removeFromBottom(14);
    g.setColour(getLookAndFeel().findColour(LCDText::ColourIds::textColour));
    g.drawRect(bounds.reduced(1), 1);
}

void PatchManager::resized()
{
    auto bounds = getLocalBounds();
    auto buttonRow = bounds.removeFromBottom(14);
    m_FileListComponent.setBounds(bounds.reduced(2));

    buttonRow.removeFromLeft(1);
    m_ChangeDir.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4.0) * 0.20));
    buttonRow.removeFromLeft(2);
    m_New.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4.0) * 0.25));
    buttonRow.removeFromLeft(2);
    m_Save.setBounds(buttonRow.removeFromLeft((bounds.getWidth() - 4.0) * 0.25));
    buttonRow.removeFromLeft(2);
    m_Delete.setBounds(buttonRow.removeFromLeft(((bounds.getWidth() - 4.0) * 0.333) - 11.0));
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

std::string PatchManager::safeName() const
{
    auto new_file = m_DirList.getDirectory().getChildFile(p_Target->getPatchName() + m_Suffix);
    int copy = 0;

    while (new_file.exists())
    {
        copy++;
        new_file = m_DirList.getDirectory().getChildFile(juce::String(p_Target->getPatchName()) + "(" + juce::String(copy) + ")" + m_Suffix);
    }

    return new_file.getFileNameWithoutExtension().toStdString();
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
        auto new_file = m_DirList.getDirectory().getChildFile(safeName() + m_Suffix);

        new_file.create();
        p_Target->savePatch(new_file);
        refreshAndSetSelected(new_file);
        startRenameSelected();
    }

    else if (btn == &m_Save)
    {
        const auto new_file = m_DirList.getDirectory().getChildFile(p_Target->getPatchName() + m_Suffix);
        p_Target->savePatch(new_file);
        refreshAndSetSelected(new_file);
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
    auto selected_point = m_FileListComponent.getRowPosition(selected_i, true);
    selected_point.removeFromLeft(selected_point.getHeight());
    selected_point.removeFromTop(2);
    m_RenameTarget = m_DirList.getFile(selected_i);
    const auto filename = m_RenameTarget.getFileName();

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

void PatchManager::textEditorEscapeKeyPressed(juce::TextEditor& editor)
{
    // Reset the name so that we don't rename things
    // when the text editor loses focus
    const auto selected_i = m_FileListComponent.getSelectedRows()[0];
    m_Editor.setText(m_DirList.getFile(selected_i).getFileName());
    m_Editor.giveAwayKeyboardFocus();
    m_Editor.setVisible(false);
}


void PatchManager::textEditorFocusLost(juce::TextEditor& editor)
{
    auto newName = m_Editor.getText();
    auto newFile = m_RenameTarget.getParentDirectory().getChildFile(newName).withFileExtension(m_Suffix);
    m_RenameTarget.moveFileTo(newFile);
    m_Editor.setVisible(false);
    refreshAndSetSelected(newFile);
}

void PatchManager::refreshAndSetSelected(const juce::File& f)
{
    m_DirList.refresh();

    while (m_DirList.isStillLoading()) {};

    m_FileListComponent.updateContent();
    m_FileListComponent.setSelectedRows(juce::SparseSet<int>(), juce::dontSendNotification);
    for (int i = 0; i < m_DirList.getNumFiles(); i++)
    {
        if (m_DirList.getFile(i) == f)
        {
            juce::SparseSet<int> rows;
            rows.addRange(juce::Range<int>(i, i + 1));
            m_FileListComponent.setSelectedRows(rows, juce::dontSendNotification);
            m_FileListComponent.scrollToEnsureRowIsOnscreen(i);
        }
    }

    m_FileListComponent.repaint();
}

void PatchManager::selectionChanged()
{
    if (m_FileListComponent.getNumSelectedFiles())
    {
        const auto selected_i = m_FileListComponent.getSelectedRows()[0];
        const auto file = m_DirList.getFile(selected_i);
        p_Target->loadPatch(file);
    }
    sendChangeMessage();
}

void PatchManager::changeTarget(Patch* target)
{
    p_Target = target;
    const auto target_file = m_DirList.getDirectory().getChildFile(p_Target->getPatchName() + m_Suffix);
    refreshAndSetSelected(target_file);
}

void PatchManager::changeDir(const juce::File& dir)
{
    m_DirList.setDirectory(dir, true, true);
}
