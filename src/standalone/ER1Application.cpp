//
// Created by mzapp on 4/15/18.
//

#include "ER1Application.h"

VirtualER1App::ER1InterfaceWindow::ER1InterfaceWindow(juce::String name)
    : juce::DocumentWindow(name, juce::Colours::lightgrey, juce::DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new VirtualER1Component(), true);
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
    setVisible (true);
}