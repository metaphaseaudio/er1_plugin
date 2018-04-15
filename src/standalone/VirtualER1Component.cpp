//
// Created by mzapp on 4/15/18.
//

#include "VirtualER1Component.h"

VirtualER1Component::VirtualER1Component()
    : editor(processor)
{
    setBounds(0, 0, 800, 600);
    addAndMakeVisible(editor);
}

void VirtualER1Component::resized()
    { editor.setBounds(getLocalBounds()); }