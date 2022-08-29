//
// Created by Mattb on 8/9/2022.
//

#pragma once
#include "LearnableSerializeableParam.h"
#include <juce_core/juce_core.h>


class Patch
{
public:
    Patch() = default;
    explicit Patch(const juce::File& loaded);

    void savePatch(const juce::File& file);
    void loadPatch(const juce::File& file);

    virtual std::string getDefaultPatchName() const { return "<default>"; }

    std::string getPatchName() const { return m_PatchName; }
    void setPatchName(const std::string& newName);

protected:
    std::string m_PatchName;

    virtual std::string getData() = 0;
    virtual void setData(const std::string& data) = 0;
};


class JSONPatch
    : public Serializeable
    , public Patch
{
public:
    void fromJson(const nlohmann::json& json) final;
    [[nodiscard]] nlohmann::json toJson() const final;

protected:
    std::string getData() override;
    void setData(const std::string& data) override;

    // We have to do it this way because patches must be named
    virtual void fromJsonInternal(const nlohmann::json& json) = 0;
    virtual nlohmann::json toJsonInternal() const = 0;
};
