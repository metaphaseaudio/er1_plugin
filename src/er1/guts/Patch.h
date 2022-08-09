//
// Created by Mattb on 8/9/2022.
//

#pragma once
#include "LearnableSerializeableParam.h"
#include <juce_core/juce_core.h>


class Patch
{
public:
    Patch();
    explicit Patch(const std::string& name);

    void savePatch(const juce::File& file);
    void loadPatch(const juce::File& file);

    std::string name;

protected:
    virtual std::string getData() = 0;
    virtual void setData(const std::string& data) = 0;
};


class JSONPatch
    : public Serializeable
    , public Patch
{
protected:
    std::string getData() override;
    void setData(const std::string& data) override;
};
