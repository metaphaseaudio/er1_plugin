//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include <guts/ER1AudioProcessor.h>
#include <gooey/ER1AudioProcessorEditor.h>
#include "VirtualER1Component.h"

class VirtualER1App
    : public juce::JUCEApplication
{
public:
    VirtualER1App() {}

    const juce::String getApplicationName() override { return "Virtual ER-1"; }
    const juce::String getApplicationVersion() override { return "0.01"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise (const juce::String& commandLine) override
        { mainWindow = new ER1InterfaceWindow (getApplicationName()); }

    void shutdown() override { mainWindow = nullptr; }
    void systemRequestedQuit() override { quit(); }
    void anotherInstanceStarted(const juce::String& commandLine) override {}

    class ER1InterfaceWindow
        : public juce::DocumentWindow
    {
    public:
        ER1InterfaceWindow(juce::String name);

        void closeButtonPressed() override
            { juce::JUCEApplication::getInstance()->systemRequestedQuit(); }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1InterfaceWindow)
    };

private:
    juce::ScopedPointer<ER1InterfaceWindow> mainWindow;
};

START_JUCE_APPLICATION(VirtualER1App);
