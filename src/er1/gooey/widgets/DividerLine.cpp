//
// Created by mzapp on 4/16/18.
//

#include "DividerLine.h"

void DividerLine::paint(juce::Graphics &g)
{
    const auto bounds = getBounds();
    const auto width = bounds.getWidth();
    const auto height = bounds.getHeight();

    g.setColour(juce::Colours::black);

    if (width > height)
    {
        const auto position = height / 2.0f;
        g.drawLine(bounds.getTopLeft().x, position, bounds.getRight(), position, 2);
    }
    else
    {
        const auto position = width / 2.0f;
        g.drawLine(position, 0, position, bounds.getBottom(), 2);
    }
}
