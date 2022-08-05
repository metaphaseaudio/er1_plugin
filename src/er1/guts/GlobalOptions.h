//
// Created by Mattb on 8/3/2022.
//

#pragma once
#include "LearnableSerializeableParam.h"
#include <juce_core/juce_core.h>
#include <atomic>
#include <meta/gooey/ChangeBroadcastingProperty.h>



class GlobalOptions
    : public Serializeable
    , public juce::ChangeBroadcaster
{
public:
    GlobalOptions();

    void fromJson(const nlohmann::json& json) override;
    nlohmann::json toJson() const override;

    void hardReset();
    void saveAsDefault();
    void loadDefault();

    meta::ChangeBroadcastingProperty<bool> enableAntialiasing;
    meta::ChangeBroadcastingProperty<bool> rotary_knobs;
    
private:

    static juce::File getDefaultsPath();
};
