//
// Created by mzapp on 4/16/18.
//

#include "GridButton.h"

GridButton::GridButton(int sequencerStep)
    : KorgButton(juce::String("Grid Step ") + juce::String(sequencerStep))
    , stepID(sequencerStep)
{
}
