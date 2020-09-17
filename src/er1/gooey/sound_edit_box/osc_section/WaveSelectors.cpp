//
// Created by Matt on 9/15/2020.
//

#include "WaveSelectors.h"

void WaveformComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds();

    g.setColour(getLookAndFeel().findColour(waveformBGColour));
    g.fillRoundedRectangle(bounds.toFloat(), 0.1f);

    g.setColour(getLookAndFeel().findColour(waveformFGColour));
    g.drawRoundedRectangle(bounds.toFloat(), 0.2f, 2);

    paintWaveform(g, bounds.reduced(2));
}


void SinWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{

}

void TriWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{}

void SquareWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{}

void NoiseWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{}

void StepWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{}

void SweepWaveform::paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds)
{}

///////////////////////////////////////////////////////////////////////////////
OscSelector::OscSelector()
{
    addIcon(&m_Sin);
    addIcon(&m_Sqr);
    addIcon(&m_Tri);
}

ModSelector::ModSelector()
{
    addIcon(&m_Sin);
    addIcon(&m_Sqr);
    addIcon(&m_Tri);
    addIcon(&m_Nse);
    addIcon(&m_Stp);
    addIcon(&m_Swp);
}

