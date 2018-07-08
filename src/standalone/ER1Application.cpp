//
// Created by mzapp on 4/15/18.
//

#include "ER1Application.h"

VirtualER1App::ER1InterfaceWindow::ER1InterfaceWindow(juce::String name)
    : juce::DocumentWindow(name, juce::Colours::lightgrey, juce::DocumentWindow::allButtons)
{
    auto safeThis = SafePointer<ER1InterfaceWindow>(this);
    auto permissionsAction = [&safeThis] (bool granted) mutable
    {
        juce::ScopedPointer<juce::XmlElement> savedAudioState(getAppProperties()
                                                             .getUserSettings()
                                                             ->getXmlValue("audioDeviceState"));

        safeThis->m_DeviceManager.initialise (granted ? 256 : 0, 256, savedAudioState, true);
    };

    juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio, permissionsAction);
    juce::ScopedPointer<juce::XmlElement> savedAudioState
            (getAppProperties().getUserSettings()->getXmlValue ("audioDeviceState"));

    setUsingNativeTitleBar(true);
    setContentOwned(new VirtualER1Component(), true);
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
    setVisible(true);
    setMenuBar(this);
}


VirtualER1App::ER1InterfaceWindow::~ER1InterfaceWindow()
{
    setMenuBar(nullptr);
}


juce::StringArray VirtualER1App::ER1InterfaceWindow::getMenuBarNames()
{ return {"File", "Options"}; }

juce::PopupMenu VirtualER1App::ER1InterfaceWindow::getMenuForIndex
(int topLevelMenuIndex, const juce::String &menuName)
{
    juce::PopupMenu menu;

    if (topLevelMenuIndex == 0)
    {
        // "File" menu
#if ! (JUCE_IOS || JUCE_ANDROID)
        menu.addCommandItem(&getCommandManager(), CommandIDs::newFile);
        menu.addCommandItem(&getCommandManager(), CommandIDs::open);
#endif

        juce::RecentlyOpenedFilesList recentFiles;
        recentFiles.restoreFromString(getAppProperties()
                                     .getUserSettings()
                                     ->getValue ("recentFiles"));

        juce::PopupMenu recentFilesMenu;
        recentFiles.createPopupMenuItems(recentFilesMenu, 100, true, true);
        menu.addSubMenu("Open recent file", recentFilesMenu);

#if ! (JUCE_IOS || JUCE_ANDROID)
        menu.addCommandItem(&getCommandManager(), CommandIDs::save);
        menu.addCommandItem(&getCommandManager(), CommandIDs::saveAs);
#endif

        menu.addSeparator();
        menu.addCommandItem(&getCommandManager(), juce::StandardApplicationCommandIDs::quit);
    }
    else if (topLevelMenuIndex == 1)
    {
        // "Options" menu
        menu.addCommandItem (&getCommandManager(), CommandIDs::showAudioSettings);
    }

    return menu;
}

void VirtualER1App::ER1InterfaceWindow::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if (menuItemID == 250)
    {
        // TODO: reset document
    }
#if ! (JUCE_ANDROID || JUCE_IOS)
    if (menuItemID >= 100 && menuItemID < 200)
    {
        juce::RecentlyOpenedFilesList recentFiles;
        recentFiles.restoreFromString(getAppProperties()
                                     .getUserSettings()
                                     ->getValue ("recentFiles"));
    }
#endif
}

juce::ApplicationCommandTarget *VirtualER1App::ER1InterfaceWindow::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void VirtualER1App::ER1InterfaceWindow::getAllCommands(juce::Array<juce::CommandID> & cmds)
{
    // this returns the set of all commands that this target can perform..
    const juce::CommandID ids[] = {
#if ! (JUCE_IOS || JUCE_ANDROID)
            CommandIDs::newFile,
            CommandIDs::open,
            CommandIDs::save,
            CommandIDs::saveAs,
#endif
            CommandIDs::showAudioSettings,
    };

    cmds.addArray (ids, juce::numElementsInArray(ids));
}

void VirtualER1App::ER1InterfaceWindow::getCommandInfo
(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{
    const juce::String category ("General");

    switch (commandID)
    {
#if ! (JUCE_IOS || JUCE_ANDROID)
        case CommandIDs::newFile:
            result.setInfo("New", "Resets state to default and starts new file", category, 0);
            result.defaultKeypresses.add(juce::KeyPress('n', juce::ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::open:
            result.setInfo("Open...", "Opens an ER-1 file", category, 0);
            result.defaultKeypresses.add(juce::KeyPress('o', juce::ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::save:
            result.setInfo("Save", "Saves the current sounds and sequences to a file", category, 0);
            result.defaultKeypresses.add(juce::KeyPress('s', juce::ModifierKeys::commandModifier, 0));
            break;

        case CommandIDs::saveAs:
            result.setInfo("Save As...", "Saves a copy of the current settings to a file", category, 0);
            result.defaultKeypresses.add(juce::KeyPress('s', juce::ModifierKeys::shiftModifier
                                                           | juce::ModifierKeys::commandModifier, 0));
            break;
#endif
        case CommandIDs::showAudioSettings:
            result.setInfo ("Change the audio device settings", juce::String(), category, 0);
            result.addDefaultKeypress ('a', juce::ModifierKeys::commandModifier);
            break;

        default:
            break;
    }
}

bool VirtualER1App::ER1InterfaceWindow::perform
(const juce::ApplicationCommandTarget::InvocationInfo&info)
{
    switch (info.commandID)
    {
#if ! (JUCE_IOS || JUCE_ANDROID)
        case CommandIDs::newFile:
            // TODO
            break;

        case CommandIDs::open:
            // TODO
            break;

        case CommandIDs::save:
            // TODO
            break;

        case CommandIDs::saveAs:
            // TODO
            break;
#endif
        case CommandIDs::showAudioSettings:
            showAudioSettings();
            break;

        default:
            return false;
    }

    return true;
}

void VirtualER1App::ER1InterfaceWindow::showAudioSettings()
{
    auto* audioSettingsComp = new juce::AudioDeviceSelectorComponent(m_DeviceManager,
                                                                     0, 256,
                                                                     0, 256,
                                                                     true, true,
                                                                     true, false);

    audioSettingsComp->setSize (500, 450);

    juce::DialogWindow::LaunchOptions o;
    o.content.setOwned (audioSettingsComp);
    o.dialogBackgroundColour =
        getLookAndFeel().findColour(juce::ResizableWindow::ColourIds::backgroundColourId);
    o.dialogTitle                   = "Audio Settings";
    o.componentToCentreAround       = this;
    o.escapeKeyTriggersCloseButton  = true;
    o.useNativeTitleBar             = false;
    o.resizable                     = false;

    auto* w = o.create();

    auto callback = [safeThis = SafePointer<ER1InterfaceWindow>(this)](int)
    {
        juce::ScopedPointer<juce::XmlElement> audioState (safeThis->m_DeviceManager.createStateXml
                ());

        getAppProperties().getUserSettings()->setValue("audioDeviceState", audioState);
        getAppProperties().getUserSettings()->saveIfNeeded();
    };

    w->enterModalState (true, juce::ModalCallbackFunction::create(callback), true);
}
