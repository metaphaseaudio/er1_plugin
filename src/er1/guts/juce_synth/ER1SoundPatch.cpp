//
// Created by Matt on 10/18/2020.
//

#include "ER1SoundPatch.h"

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


ER1SoundPatch::ER1SoundPatch(std::string name, OscParams osc, AmpParams amp, DelayParams delay, unsigned int midiNoteNumber, unsigned int
midiChannel)
    : config(nullptr)
    , amp(amp)
    , osc(osc)
    , delay(delay)
{
    name = name;
}

void ER1SoundPatch::printStatus()
{
    std::cout << m_PatchName << std::endl;
    std::cout << "Note: " << config->note << std::endl;
    std::cout << "Chan: " << config->chan << std::endl;
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

json ER1SoundPatch::toJsonInternal() const
{
    return json({
        {"osc", osc.asJSON()},
        {"amp", amp.asJSON()},
        {"delay", delay.asJSON()},
    });
}

void ER1SoundPatch::fromJsonInternal(const json& j)
{
    try
    {
        osc.fromJSON(j["osc"]);
        amp.fromJSON(j["amp"]);
        delay.fromJSON(j["delay"]);
    }
    catch (json::exception& err)
    {
        std::cout << "Failed to load ER-1 control state:" << err.what() << std::endl;
    }
}
