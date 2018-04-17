//
// Created by mzapp on 4/16/18.
//

#include "SequencerButton.h"

SequencerButton::SequencerButton(int sequencerStep)
    : KorgButton(juce::String("Sequencer Step ") + juce::String(sequencerStep))
    , stepID(sequencerStep)
{
}
