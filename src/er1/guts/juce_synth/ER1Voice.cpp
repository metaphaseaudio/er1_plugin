//
// Created by Matt on 9/27/2020.
//

#include "ER1Voice.h"
#include "er1_dsp/sounds/AnalogSound.h"
#include "er1_dsp/sounds/PCMSound.h"

ER1Voice::ER1Voice(ER1ControlBlock::Ptr& sound, meta::ER1::BaseSound* voice)
    : p_Ctrls(sound)
    , m_Sound(voice)
{}

void ER1Voice::startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition)
{
    m_Sound->reset();
    m_Sound->start();
}

void ER1Voice::setSampleRate(double newRate)
    { m_Sound->setSampleRate(newRate); }

void ER1Voice::updateParams()
{
    if (dynamic_cast<meta::ER1::AnalogSound*>(m_Sound.get()) != nullptr)
    {
        m_Sound->setWaveShape(static_cast<meta::ER1::Wave::Shape>(p_Ctrls->osc.oscType->getIndex()));
        m_Sound->setModulationShape(static_cast<meta::ER1::Mod::Shape>(p_Ctrls->osc.modType->getIndex()));
        m_Sound->setModulationSpeed(p_Ctrls->osc.modSpeed->get());
        m_Sound->setModulationDepth(p_Ctrls->osc.modDepth->get());
        m_Sound->setPitch(p_Ctrls->osc.pitch->get());
    }

    if (dynamic_cast<meta::ER1::PCMSound*>(m_Sound.get()) != nullptr)
    {
        m_Sound->setPitch(p_Ctrls->osc.pitch->get());
    }

    m_Sound->setDecay(p_Ctrls->amp.decay->get());

    m_Channel.setLowBoost(p_Ctrls->amp.lowBoost->get());
    m_Channel.setLevel(p_Ctrls->amp.level->get());
    m_Channel.setPan(p_Ctrls->amp.pan->get());
    m_Channel.setTempoSync(true);
    m_Channel.setTempo(120);
    m_Channel.setDelayTime(p_Ctrls->delay.time->get());
    m_Channel.setDelayDepth(p_Ctrls->delay.depth->get());
    m_Channel.setTempoSync(p_Ctrls->delay.sync->get());
}


void ER1Voice::processBlock(float** inData, float** outData, const float* lastData, int samps, int offset)
{
    const auto* ringData = isRingModCarrier() ? lastData : nullptr;
    auto* tmpData = inData[m_Sound->wantsAudioChannel()];
    m_Sound->processBlock(tmpData, ringData, samps, offset);
    m_Channel.processBlock(tmpData, outData, samps, offset);
}
