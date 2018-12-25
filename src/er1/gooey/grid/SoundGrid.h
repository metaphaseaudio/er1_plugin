//
// Created by mzapp on 12/24/18.
//

#pragma once

#include <meta/gooey/RadioGrid.h>
#include "../widgets/KorgButton.h"

class SoundGrid
    : public meta::RadioGrid<KorgToggleButton, 4, 4>
{
    void gridButtonClicked(juce::Button* btn) override {};
};
