//
// Created by mzapp on 4/15/18.
//

#include "VirtualER1Component.h"

VirtualER1Component::VirtualER1Component()
{
    m_Laf  = new ER1LAF();
    editor = new ER1AudioProcessorEditor(processor);
    setLookAndFeel(m_Laf);
    addAndMakeVisible(editor);
    auto desiredBounds = editor->getBounds();
    setBounds(0, 0, desiredBounds.getWidth(), desiredBounds.getHeight());
}

void VirtualER1Component::resized()
    { editor->setBounds(getLocalBounds()); }

VirtualER1Component::~VirtualER1Component()
    { setLookAndFeel(nullptr); }
