//
// Created by Matt on 9/9/2020.
//
#include "SequenceGrid.h"

SequenceGrid::SequenceGrid(int bpm)
        : m_BPM(bpm)
{}

void SequenceGrid::timerCallback()
{

}

int SequenceGrid::getBpm() const { return m_BPM; }

void SequenceGrid::setBpm(int bpm)
{
    m_BPM = bpm;
    startTimer(60000 / bpm);
}
