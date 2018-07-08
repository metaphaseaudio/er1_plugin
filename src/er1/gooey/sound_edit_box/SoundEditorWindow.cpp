//
// Created by mzapp on 7/8/18.
//

#include "SoundEditorWindow.h"
#include "../look_and_feel/ER1Colours.h"

void SoundEditorWindow::resized()
{
    auto bounds = getLocalBounds().reduced(2);
}

void SoundEditorWindow::paint(juce::Graphics& g)
{
    g.fillAll(ER1Colours::defaultBackground);
    g.setColour(juce::Colours::black);
    auto bounds = getLocalBounds();
    g.drawRect(bounds, 2);
}
