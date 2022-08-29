//
// Created by Mattb on 8/9/2022.
//

#include "Patch.h"


Patch::Patch(const juce::File& loaded)
    { loadPatch(loaded); }

void Patch::savePatch(const juce::File& f)
{
    auto stream = f.createOutputStream();
    stream->setPosition(0);
    stream->truncate();
    stream->writeString(getData());
    stream->flush();
    stream.reset(nullptr);
}

void Patch::loadPatch(const juce::File& file)
{
    const auto reader = file.createInputStream();
    setData(reader->readEntireStreamAsString().toStdString());
    m_PatchName = file.getFileNameWithoutExtension().toStdString();
}

void Patch::setPatchName(const std::string& newName)
{
    m_PatchName = newName;
}


std::string JSONPatch::getData()
{
    auto j = toJson();
    return j.dump(4);
}

void JSONPatch::setData(const std::string& data)
{
    try
    {
        auto j = nlohmann::json::parse(data);
        fromJson(j);
    }
    catch (nlohmann::json::exception& err)
        { std::cout << err.what() << std::endl; }
}

void JSONPatch::fromJson(const nlohmann::json& json)
{
    m_PatchName = json.value("patch_name", "<default>");
    fromJsonInternal(json);
}

nlohmann::json JSONPatch::toJson() const
{
    auto rv = toJsonInternal();
    rv["patch_name"] = m_PatchName;
    return rv;
}
