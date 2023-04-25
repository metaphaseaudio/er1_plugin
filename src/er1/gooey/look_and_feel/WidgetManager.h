//
// Created by Matt on 4/22/2023.
//
#pragma once
#include <string>
#include <map>
#include <juce_gui_basics/juce_gui_basics.h>
#include "meta/gooey/Filmstrip.h"


class WidgetManager
{
public:
    struct WidgetInfo
    {
        meta::Filmstrip filmstrip;
        juce::Point<int> position;
    };

    enum WidgetID
    {
        // Knob names
        pitch = 0, mod_speed, mod_depth, level, decay, pan, low_boost, delay_time, delay_depth,
        // Button names
        listen, sound, bank, options, ring_btn, tempo_sync, sound_btn
    };

    enum WidgetVariant
    {
        // Button lighting types
        standard = 0,
        lit,
        brighter,
        hover
    };

    WidgetManager();

    [[nodiscard]] const WidgetInfo& getWidgetInfo(WidgetID widget_id, WidgetVariant variant, int index) const;

private:
    std::map<WidgetID, std::map<WidgetVariant, std::vector<WidgetInfo>>> m_WidgetInfo;
};
