//
// Created by mzapp on 12/24/18.
//
#pragma once

#include <meta/gooey/ComponentGrid.h>
#include "../widgets/KorgPad.h"

class PadGrid
    : public meta::ComponentGrid<KorgPad, 4, 4>
{
public:
    explicit PadGrid(meta::MidiState& state)
        : ComponentGrid(state)
    {}

    void setNoteForPad(size_t button_i, uint8_t midi_note) { m_Children.at(button_i)->note = midi_note; }
    uint8_t getNoteForPad(size_t button_i) { return m_Children.at(button_i)->note; }

private:
};
