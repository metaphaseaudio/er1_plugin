//
// Created by Matt on 6/10/2022.
//

#include "Arrows.h"

static constexpr int pointerSize = 0;
static constexpr int lineWidth = 2;

void Arrow::UpAndRight::paint(juce::Graphics& g)
{
    const auto bounds = getLocalBounds();
    const auto halfPtr = pointerSize / 2.0f;
    const auto tl = bounds.getTopLeft();
    const auto tr = bounds.getTopRight();
    const auto up = m_Mirrored
            ? juce::Rectangle<float>(tr.x - lineWidth, tr.y - halfPtr, lineWidth, bounds.getHeight() - halfPtr)
            : juce::Rectangle<float>(tl.x, tl.y + halfPtr, lineWidth, bounds.getHeight() - halfPtr);
    const auto across = juce::Rectangle<float>(tl.x, tl.y + halfPtr, bounds.getWidth(), lineWidth);
    g.setColour(juce::Colours::black);
    g.fillRect(up);
    g.fillRect(across);
}

Arrow::UpAndRight::UpAndRight(bool mirrored)
    : m_Mirrored(mirrored)
{}
