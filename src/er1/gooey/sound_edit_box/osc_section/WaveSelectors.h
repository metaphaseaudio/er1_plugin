//
// Created by Matt on 9/15/2020.
//

#pragma once

#include "../../widgets/SelectorButton.h"


class WaveformComponent
    : public juce::Component
{
public:

    void paint(juce::Graphics& g) override;

    virtual void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) = 0;

    enum ColourIds
    {
        waveformFGColour = 0x1002100,
        waveformBGColour = 0x1002101
    };
};

class SinWaveform : public WaveformComponent    { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };
class TriWaveform : public WaveformComponent    { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };
class SquareWaveform : public WaveformComponent { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };
class NoiseWaveform : public WaveformComponent  { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };
class StepWaveform : public WaveformComponent   { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };
class SweepWaveform : public WaveformComponent  { void paintWaveform(juce::Graphics& g, juce::Rectangle<int> bounds) override; };


class OscSelector
    : public SelectorButton
{
public:
    OscSelector();

private:
    SinWaveform m_Sin;
    TriWaveform m_Tri;
    SquareWaveform m_Sqr;
};


class ModSelector
    : public SelectorButton
{
public:
    ModSelector();

private:
    SinWaveform m_Sin;
    TriWaveform m_Tri;
    SquareWaveform m_Sqr;
    NoiseWaveform m_Nse;
    StepWaveform m_Stp;
    SweepWaveform m_Swp;
};

