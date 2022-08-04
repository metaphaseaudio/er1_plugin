//
// Created by Mattb on 8/3/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../guts/GlobalOptions.h"

class ToggleOptionComponent
    : public juce::Component
    , juce::Button::Listener
{
public:
    ToggleOptionComponent(const std::string& label, meta::ChangeBroadcastingProperty<bool>& option);
    void buttonClicked(juce::Button* button) override;
    void resized() override;

private:
    juce::Label m_Label;
    juce::ToggleButton m_OptToggle;
    meta::ChangeBroadcastingProperty<bool>& m_Opt;
};

class OptionsListBoxModel
    : public juce::ListBoxModel
{
public:
    explicit OptionsListBoxModel(GlobalOptions& opts);
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;

private:
    std::vector<std::unique_ptr<juce::Component>> m_Components;
};


class OptionsComponent
    : public juce::Component
{
public:
    explicit OptionsComponent(GlobalOptions& opts);
    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    OptionsListBoxModel m_Options;
    juce::ListBox m_OptionsListBox;

};
