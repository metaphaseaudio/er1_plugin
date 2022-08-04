//
// Created by Mattb on 8/3/2022.
//

#include "GlobalOptions.h"


GlobalOptions::GlobalOptions()
    : enableAntialiasing(false)
    , rotary_knobs(false)
{
    loadDefault();
}

void GlobalOptions::fromJson(const nlohmann::json& json)
{
    enableAntialiasing = json.value("enableAntialiasing", false);
    rotary_knobs = json.value("rotary_knobs", false);
}

nlohmann::json GlobalOptions::toJson() const
{
    return nlohmann::json({
        {"enableAntialiasing", enableAntialiasing.load()},
        {"rotary_knobs", rotary_knobs.load()}
    });
}

juce::File GlobalOptions::getDefaultsPath()
{
    return juce::File::getSpecialLocation(juce::File::SpecialLocationType::commonApplicationDataDirectory)
                      .getChildFile("metaphase")
                      .getChildFile("er_1_defaults.json");
}

void GlobalOptions::saveAsDefault()
{
    const auto defaults = getDefaultsPath();
    auto stream = defaults.createOutputStream();
    stream->setPosition(0);
    stream->truncate();
    stream->writeString(toJson().dump(4));
    stream->flush();
    stream.reset(nullptr);
}

void GlobalOptions::loadDefault()
{
    const auto defaults = getDefaultsPath();

    if (defaults.exists())
    {
        const auto stream = defaults.createInputStream();
        try
        {
            nlohmann::json j = nlohmann::json::parse(stream->readString().toStdString());
            fromJson(j);
        }
        catch (nlohmann::json::exception& err)
        {
            std::cout << "Failed to load default state file, using built-in default" << std::endl;
            hardReset();
        }
    }
    else
    {
        hardReset();
    }
}

void GlobalOptions::hardReset()
{
    enableAntialiasing = false;
    rotary_knobs = false;
}
