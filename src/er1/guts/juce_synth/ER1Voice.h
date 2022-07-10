//
// Created by Matt on 9/27/2020.
//

#pragma once
#include <juce_audio_basics/juce_audio_basics.h>
#include "er1_dsp/sounds/BaseSound.h"
#include "ER1ControlBlock.h"
#include "er1_dsp/Channel.h"


class ER1Voice
{
public:
    ER1Voice(ER1ControlBlock::Ptr& sound, meta::ER1::BaseSound* voice);
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition);
    void updateParams(float tempo);
    void setSampleRate(double sr);
    void setMaxBusCount(int busCount) { m_BusCount = busCount; }
    void addToChokeList(ER1Voice* voice) { m_Sound->addSoundToChokeList(voice->m_Sound.get()); }
    void processBlock(float** inData, float** outData, const float* lastData, int samps, int offset);

    [[nodiscard]] ER1ControlBlock::Ptr getControlBlock() const { return p_Ctrls; }
    [[nodiscard]] float getDecayEnvValue() const { return m_Sound->getEnvValue(); }

    [[ nodiscard ]] bool appliesToNote (int midiNoteNumber) const { return midiNoteNumber == p_Ctrls->config.note || p_Ctrls->config.noteFollow; };
    [[ nodiscard ]] bool appliesToChannel (int midiChannel) const { return midiChannel == p_Ctrls->config.chan; };
    [[ nodiscard ]] bool isRingModCarrier() const { return p_Ctrls->osc.enableRing != nullptr && p_Ctrls->osc.enableRing->get(); }

private:
    int m_BusCount = 1;
    ER1ControlBlock::Ptr p_Ctrls;
    std::unique_ptr<meta::ER1::BaseSound> m_Sound;
    meta::ER1::Channel m_Channel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ER1Voice);
};


