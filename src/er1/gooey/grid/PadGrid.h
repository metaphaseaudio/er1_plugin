//
// Created by mzapp on 12/24/18.
//
#pragma once

#include <meta/gooey/ButtonGrid.h>
#include "../widgets/KorgButton.h"

class PadGrid
    : public meta::ButtonGrid<KorgButton, 4, 4>
{
    void gridButtonClicked(juce::Button* btn) override {};
};
