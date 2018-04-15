/*
  ==============================================================================

    Transport.cpp
    Created: 1 Apr 2018 3:20:35am
    Author:  Matt Zapp

  ==============================================================================
*/

#include "Transport.h"

using namespace juce;

Transport::Transport() {}

Transport::~Transport() {}

void Transport::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour(ResizableWindow::backgroundColourId));  
}

void Transport::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
