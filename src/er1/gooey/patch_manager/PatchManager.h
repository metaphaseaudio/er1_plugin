//
// Created by Mattb on 6/23/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class PatchManager
    : public juce::Component
    , juce::FileBrowserListener
{
public:
    PatchManager();
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

    juce::WildcardFileFilter m_ImagesWildcardFilter  { "*.jpeg;*.jpg;*.png;*.gif", "*", "Image File Filter"};
    juce::TimeSliceThread m_DirectoryThread          { "Image File Scanner Thread" };
    juce::DirectoryContentsList m_ImageList          { &m_ImagesWildcardFilter, m_DirectoryThread };
    juce::FileListComponent m_FileTree               { m_ImageList };
};
