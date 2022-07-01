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
    if (p_Ctrls->config.noteFollow)
    {
        constexpr float frequencyOfA = 440;
        const auto pitch = p_Ctrls->osc.pitch != nullptr ? p_Ctrls->osc.pitch->get() : 0.5f;
        const float noteNumber = float(midiNoteNumber) + meta::Interpolate<float>::linear(-12.0f, 12.0f, pitch);
        const float midiPitch = frequencyOfA * std::pow(2.0, (noteNumber - 69) / 12.0);
        m_Sound->setPitch(midiPitch);
    }

    m_Sound->reset();
    m_Sound->start();
    m_Channel.setAccentGain(meta::Interpolate<float>::parabolic(0.1, 1.0, velocity, 1.5f));

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

        if (!p_Ctrls->config.noteFollow)
            { m_Sound->setPitch(meta::Interpolate<float>::parabolic(20.0f, 20000.0, p_Ctrls->osc.pitch->get(), 5)); }
    }

    if (dynamic_cast<meta::ER1::PCMSound*>(m_Sound.get()) != nullptr)
        { m_Sound->setPitch(p_Ctrls->osc.pitch->get()); }

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

    // Skip render if the bus is out of scope.
    if (p_Ctrls->config.bus.load() >= m_BusCount){ return; }
    const auto busIndex = std::max(0, std::min<int>(m_BusCount - 1, p_Ctrls->config.bus.load()));
    m_Channel.processBlock(tmpData, outData != nullptr ? outData + (2 * busIndex) : nullptr, samps, offset);
}
