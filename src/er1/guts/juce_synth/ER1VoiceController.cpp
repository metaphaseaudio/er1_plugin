//
// Created by Matt on 9/27/2020.
//

#include "ER1VoiceController.h"

ER1Voice::ER1Voice(ER1Sound::Ptr sound)
    : m_Sound(sound)
    , m_Voice(48000 * meta::ER1::MainOscillator::OverSample)
{}

void ER1Voice::startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition)
{
    m_Voice.reset();
    m_Voice.start();
}

void ER1Voice::setSampleRate(double newRate) { m_Voice.setSampleRate(newRate); }

void ER1Voice::updateParams()
{
    m_Voice.setWaveShape(static_cast<meta::ER1::WaveShape>(m_Sound->osc.oscType->getIndex()));
    m_Voice.setModulationShape(static_cast<meta::ER1::AnalogVoice::ModShape>(m_Sound->osc.modType->getIndex()));
    m_Voice.setModulationSpeed(m_Sound->osc.modSpeed->get());
    m_Voice.setModulationDepth(m_Sound->osc.modDepth->get());
    m_Voice.setPitch(meta::Interpolate<float>::parabolic(20.0f, 12000.0, m_Sound->osc.pitch->get(), 4));
    m_Voice.setDecay(m_Sound->amp.decay->get());
    m_Channel.setLevel(m_Sound->amp.level->get());
    m_Channel.setPan(m_Sound->amp.pan->get());
    m_Channel.setTempoSync(true);
    m_Channel.setTempo(120);
    m_Channel.setDelayTime(m_Sound->delay.time->get());
    m_Channel.setDelayDepth(m_Sound->delay.depth->get());
    m_Channel.setTempoSync(m_Sound->delay.sync->get());
}

