//
// Created by Matt on 4/22/2023.
//
#include "WidgetManager.h"
#include "meta/util/StringHelpers.h"


WidgetManager::WidgetManager()
{
    std::map<std::string, WidgetID> nameMap = {
        { "pitch", pitch },
        { "mod_speed", mod_speed },
        { "mod_depth", mod_depth },
        { "level", level },
        { "decay", decay },
        { "pan", pan },
        { "low_boost", low_boost },
        { "delay_time", delay_time },
        { "delay_depth", delay_depth },
        { "listen", listen },
        { "sound", sound },
        { "bank", bank },
        { "options", options },
        { "ring_btn", ring_btn },
        { "tempo_sync", tempo_sync },
        { "sound_btn", sound_btn }
    };

    std::map<std::string, WidgetVariant> variantMap = {
        { "standard" , standard },
        { "hover" , hover }
    };

    auto widgetZipFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory)
                       .getChildFile("Metaphase")
                       .getChildFile("ER-1")
                       .getChildFile("widgets.zip");

    auto zip = juce::ZipFile(widgetZipFile);
    std::vector<juce::ZipFile::ZipEntry> zipEntries;

    // I want to get rid of this stupid crap, the data should be arranged in a way that's pre-sorted.
    std::vector<std::tuple<int, std::string>> nameIndexPairs;
    for (int i = zip.getNumEntries(); --i >= 0;)
        { nameIndexPairs.emplace_back(i, zip.getEntry(i)->filename.toStdString()); }

    std::sort(nameIndexPairs.begin(), nameIndexPairs.end(), [](auto x, auto y){
        auto tokens_x = meta::StringHelpers::split(std::get<1>(x), "-");
        auto tokens_y = meta::StringHelpers::split(std::get<1>(y), "-");
        auto xI = std::stoi(tokens_x.at(2));
        auto yI = std::stoi(tokens_y.at(2));

        return xI < yI;
    });

    for(auto pair : nameIndexPairs)
    {
        auto i = std::get<0>(pair);
        auto entryInfo = zip.getEntry(i);
        std::unique_ptr<juce::InputStream> entryStream(zip.createStreamForEntry(i));
        auto tokens = meta::StringHelpers::split(entryInfo->filename.toStdString(), "-");
        auto widgetName = nameMap[tokens.at(0)];
        auto variant = variantMap[tokens.at(1)];
        auto widgetIndex = std::stoi(tokens.at(2));
        auto frameCount = std::stoi(tokens.at(3));
        auto xy = meta::StringHelpers::split(tokens.at(4), "_");
        auto y = std::stoi(xy.at(0));
        auto x = std::stoi(xy.at(1));

        juce::MemoryBlock mem(entryStream->getTotalLength());
        entryStream->read(mem.getData(), static_cast<size_t>(entryStream->getTotalLength()));

        m_WidgetInfo[widgetName][variant].emplace_back(
            std::move(WidgetInfo{meta::Filmstrip(juce::ImageFileFormat::loadFrom(mem.getData(), mem.getSize()), frameCount, meta::Orientation::VERT),
            juce::Point<int>(y, x)})
        );

        jassert(widgetIndex + 1 == m_WidgetInfo[widgetName][variant].size());
    }
}

const WidgetManager::WidgetInfo&
WidgetManager::getWidgetInfo(WidgetManager::WidgetID widget_id, WidgetManager::WidgetVariant variant, int index) const
    { return m_WidgetInfo.at(widget_id).at(variant).at(index); }

