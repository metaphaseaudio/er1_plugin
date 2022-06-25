//
// Created by Mattb on 6/23/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/LCDButton.h"


class PatchManager
    : public juce::Component
    , juce::FileBrowserListener
    , juce::Button::Listener
{
public:
    PatchManager(const juce::File& startingDir, const std::string& name, const juce::WildcardFileFilter& filter);
    ~PatchManager() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void selectionChanged() override
    {
        // TODO: update the global or individual-sound patch and trigger a re-paint
    }

    void fileClicked (const juce::File&, const juce::MouseEvent&) override {}
    void fileDoubleClicked (const juce::File&) override;
    void browserRootChanged (const juce::File&) override {}

    void buttonClicked(juce::Button* btn) override;

    juce::WildcardFileFilter m_WildcardFilter;
    juce::TimeSliceThread m_DirectoryThread;
    juce::DirectoryContentsList m_FileList {&m_WildcardFilter, m_DirectoryThread };
    juce::FileListComponent m_FileTree {m_FileList};

    LCDButton m_ChangeDir, m_New, m_Delete;
};
