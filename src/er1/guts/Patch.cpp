//
// Created by Mattb on 8/9/2022.
//

#include "Patch.h"

Patch::Patch()
    : name("")
{

}

Patch::Patch(const std::string& name)
    : name(name)
{}

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
}


std::string JSONPatch::getData()
{
    auto j = toJson();
    j["patch_name"] = name;
    return toJson().dump(4);
}
void JSONPatch::setData(const std::string& data)
{
    try
    {
        auto j = nlohmann::json::parse(data);
        name = j.value("patch_name", "");
        fromJson(j);
    }
    catch (nlohmann::json::exception& err)
    { std::cout << err.what() << std::endl; }
}
