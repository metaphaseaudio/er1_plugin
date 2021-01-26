//
// Created by mzapp on 12/24/18.
//
#pragma once

#include <meta/gooey/ButtonGrid.h>
#include "../widgets/KorgButton.h"

class SequenceGrid
    : public meta::ButtonGrid<KorgToggleButton, 4, 4>
    , juce::Timer
{
public:
    SequenceGrid(int bpm=120);
    int getBpm() const;
    void setBpm(int mBpm);

private:
    void timerCallback() override;
    void gridButtonClicked(juce::Button* btn) override {}

    int m_BPM;
};
