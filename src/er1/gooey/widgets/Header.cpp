//
// Created by Mattb on 6/27/2022.
//

#include "Header.h"

void Header::paint(juce::Graphics& g)
{
    const auto localBounds = getLocalBounds().toFloat();
    
    juce::Path text;
    juce::GlyphArrangement arr;
    arr.addFittedText(
            g.getCurrentFont().boldened(),
            getName(),
            localBounds.getX(),
            localBounds.getY(),
            localBounds.getWidth(),
            localBounds.getHeight(),
            juce::Justification::centred, 1
    );
    arr.createPath(text);

    juce::Path rect;
    rect.addRectangle(localBounds);
    rect.setUsingNonZeroWinding(false);
    rect.addPath(text);
    g.setColour(juce::Colours::black);
    g.fillPath(rect);
}
