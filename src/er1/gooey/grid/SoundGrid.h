//
// Created by mzapp on 12/24/18.
//

#pragma once

#include <meta/gooey/RadioGrid.h>
#include "../widgets/KorgButton.h"

class SoundGrid
    : public meta::RadioGrid<KorgToggleButton, 1, 16>
{
    void gridButtonClicked(juce::Button* btn) override {};
};
