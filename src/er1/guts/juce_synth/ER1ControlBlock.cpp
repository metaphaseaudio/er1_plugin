//
// Created by Matt on 10/18/2020.
//

#include "ER1ControlBlock.h"

static juce::StringArray OscNames =
{
    "Sine"
    , "Triangle"
};

static juce::StringArray ModulationNames =
{
    "Saw"
    , "Square"
    , "Triangle"
    , "SAH"
    , "Noise"
    , "Decay"
};


ER1ControlBlock::ER1ControlBlock(OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int midiChannel)
    : config{"New Sound", midiNoteNumber, midiChannel}
    , amp(amp)
    , osc(osc)
    , delay(delay)
{}

void ER1ControlBlock::printStatus()
{
    std::cout << config.name << std::endl;
    std::cout << "Note: " << config.note << std::endl;
    std::cout << "Chan: " << config.chan << std::endl;
    std::cout << "Shape: " << osc.oscType->getCurrentValueAsText() << std::endl;
    std::cout << "Pitch: " << osc.pitch->getCurrentValueAsText() << std::endl;
    std::cout << "Mod Type: " << osc.modType->getCurrentValueAsText() << std::endl;
    std::cout << "Mod Speed: " << osc.modSpeed->getCurrentValueAsText() << std::endl;
    std::cout << "Mod Depth: " << osc.modDepth->getCurrentValueAsText() << std::endl;
    std::cout << std::endl;

    std::cout << "Decay: " << amp.decay->getCurrentValueAsText() << std::endl;
    std::cout << "Level: " << amp.level->getCurrentValueAsText() << std::endl;
    std::cout << "Pan: " << amp.pan->getCurrentValueAsText() << std::endl;
    std::cout << "Boost: " << amp.lowBoost->getCurrentValueAsText() << std::endl;
    std::cout << std::endl;

    std::cout << "Delay Depth: " << delay.depth->getCurrentValueAsText() << std::endl;
    std::cout << "Delay Time: " << delay.time->getCurrentValueAsText() << std::endl;
    std::cout << "Delay Sync: " << delay.sync->getCurrentValueAsText() << std::endl;
    std::cout << std::endl;
}
