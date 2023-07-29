//
// Created by Mattb on 6/23/2022.
//

#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "widgets/LCDButton.h"
#include "../guts/Patch.h"


class PatchManager
    : public juce::Component
    , public juce::ChangeBroadcaster
    , juce::TextEditor::Listener
    , juce::FileBrowserListener
    , juce::Button::Listener
{
public:
    PatchManager(Patch* target, const juce::File& startingDir, const std::string& name, const std::string& customSuffix="*.json");
    ~PatchManager() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

    void changeTarget(Patch* target);
    juce::File getCurrentDirectory() const { return m_DirList.getDirectory(); };
    void changeDir(const juce::File& dir);

private:
    void textEditorReturnKeyPressed(juce::TextEditor& editor) override;
    void selectionChanged() override;

    std::string safeName() const;
    void startRenameSelected();
    void refreshAndSetSelected(const juce::File& f);

    void textEditorFocusLost(juce::TextEditor& editor) override;

    void fileClicked (const juce::File&, const juce::MouseEvent&) override {}
    void fileDoubleClicked (const juce::File&) override;
    void browserRootChanged (const juce::File&) override {}

    void buttonClicked(juce::Button* btn) override;

    Patch* p_Target;
    std::string m_Suffix;
    juce::TextEditor m_Editor;
    juce::WildcardFileFilter m_WildcardFilter;
    juce::TimeSliceThread m_DirectoryThread;
    juce::DirectoryContentsList m_DirList {&m_WildcardFilter, m_DirectoryThread };
    juce::FileListComponent m_FileListComponent {m_DirList};
    std::unique_ptr<juce::FileChooser> m_FileChooser;

    LCDButton m_ChangeDir, m_New, m_Save, m_Delete;
};
