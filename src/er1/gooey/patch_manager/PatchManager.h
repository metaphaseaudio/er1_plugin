//
// Created by Mattb on 6/23/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/gooey/FileListComponent.h>
#include "../widgets/LCDButton.h"
#include "../../guts/LearnableSerializeableParam.h"


class PatchManager
    : public juce::Component
    , juce::FileBrowserListener
    , juce::Button::Listener
{
public:
    PatchManager(Serializeable* target, const juce::File& startingDir, const std::string& name, const std::string& customSuffix="*.json");
    ~PatchManager() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void selectionChanged() override
    {
        // TODO: update the global or individual-sound patch and trigger a re-paint
    }

    void startRenameSelected();

    void fileClicked (const juce::File&, const juce::MouseEvent&) override {}
    void fileDoubleClicked (const juce::File&) override;
    void browserRootChanged (const juce::File&) override {}

    void buttonClicked(juce::Button* btn) override;

    Serializeable* p_Target;
    std::string m_Suffix;
    juce::TextEditor m_Editor;
    juce::WildcardFileFilter m_WildcardFilter;
    juce::TimeSliceThread m_DirectoryThread;
    juce::DirectoryContentsList m_DirList {&m_WildcardFilter, m_DirectoryThread };
    meta::FileListComponent m_FileListComponent {m_DirList};
    std::unique_ptr<juce::FileChooser> m_FileChooser;

    LCDButton m_ChangeDir, m_New, m_Delete;
};
