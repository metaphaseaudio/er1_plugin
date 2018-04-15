/*
  ==============================================================================

    RedBox.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "RedBox.h"

using namespace juce;

RedBox::RedBox() {}

RedBox::~RedBox() {}

void RedBox::paint (Graphics& g)
{
	g.fillAll(juce::Colour::fromRGB(0xEB, 0x4D, 0x66));   // clear the background

    g.setColour(getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.drawRect(getLocalBounds(), 2);   // draw an outline around the component
}

void RedBox::resized() {}
