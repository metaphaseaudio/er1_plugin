//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <JuceHeader.h>
#include <guts/ER1AudioProcessor.h>
#include <gooey/ER1AudioProcessorEditor.h>
#include "VirtualER1Component.h"

namespace CommandIDs
{
#if ! (JUCE_IOS || JUCE_ANDROID)
    static const int open                   = 0x30000;
    static const int save                   = 0x30001;
    static const int saveAs                 = 0x30002;
    static const int newFile                = 0x30003;
#endif
    static const int showAudioSettings      = 0x30100;
}

class VirtualER1App
    : public juce::JUCEApplication
{
public:
    VirtualER1App() {}

    const juce::String getApplicationName() override { return "Virtual ER-1"; }
    const juce::String getApplicationVersion() override { return "0.01"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise (const juce::String& commandLine) override
    {
        juce::PropertiesFile::Options options;
        options.applicationName     = "Virtual ER-1";
        options.filenameSuffix      = "settings";
        options.osxLibrarySubFolder = "Preferences";

        appProperties = new juce::ApplicationProperties();
        appProperties->setStorageParameters(options);

        mainWindow = new ER1InterfaceWindow(getApplicationName());
        mainWindow->setUsingNativeTitleBar(true);

        commandManager.registerAllCommandsForTarget (this);
        commandManager.registerAllCommandsForTarget (mainWindow);
        mainWindow->menuItemsChanged();
    }

    void shutdown() override { mainWindow = nullptr; }
    void systemRequestedQuit() override { quit(); }
    void anotherInstanceStarted(const juce::String& commandLine) override {}

    class ER1InterfaceWindow
        : public juce::DocumentWindow
        , public juce::MenuBarModel
        , public juce::ApplicationCommandTarget
    {
    public:
        ER1InterfaceWindow(juce::String name);

        juce::StringArray getMenuBarNames() override;
        juce::PopupMenu getMenuForIndex (int topLevelMenuIndex, const juce::String& menuName) override;
        void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
        juce::ApplicationCommandTarget* getNextCommandTarget() override;
        void getAllCommands (juce::Array<juce::CommandID>&) override;
        void getCommandInfo (juce::CommandID, juce::ApplicationCommandInfo&) override;
        bool perform (const InvocationInfo&) override;

        void showAudioSettings();

        void closeButtonPressed() override
            { juce::JUCEApplication::getInstance()->systemRequestedQuit(); }

    private:
        juce::AudioDeviceManager m_DeviceManager;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ER1InterfaceWindow)
    };

    juce::ApplicationCommandManager commandManager;
    juce::ScopedPointer<juce::ApplicationProperties> appProperties;

private:
    juce::ScopedPointer<ER1InterfaceWindow> mainWindow;

};

static VirtualER1App& getApp()
    { return *dynamic_cast<VirtualER1App*>(juce::JUCEApplication::getInstance()); }
juce::ApplicationProperties& getAppProperties() { return *getApp().appProperties; }
juce::ApplicationCommandManager& getCommandManager() { return getApp().commandManager; }
bool isOnTouchDevice() { return juce::Desktop::getInstance().getMainMouseSource().isTouch(); }

START_JUCE_APPLICATION(VirtualER1App);
