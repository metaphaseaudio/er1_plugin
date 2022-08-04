//
// Created by Mattb on 8/3/2022.
//

#include "Options.h"
#include "look_and_feel/ER1Colours.h"


void ToggleOptionComponent::buttonClicked(juce::Button* button)
{
    m_Opt = m_OptToggle.getToggleState();
}

ToggleOptionComponent::ToggleOptionComponent(const std::string& label, meta::ChangeBroadcastingProperty<bool>& option)
    : m_Label(label, label)
    , m_Opt(option)
{
    addAndMakeVisible(m_Label);
    addAndMakeVisible(m_OptToggle);
    m_OptToggle.addListener(this);
    m_OptToggle.setToggleState(option.load(), juce::NotificationType::dontSendNotification);
}

void ToggleOptionComponent::resized()
{
    auto localBounds = getLocalBounds();
    m_Label.setBounds(localBounds.removeFromLeft(m_Label.getFont().getStringWidthFloat(m_Label.getText()) + 15));
    m_OptToggle.setBounds(localBounds.removeFromLeft(localBounds.getHeight()));
}


OptionsListBoxModel::OptionsListBoxModel(GlobalOptions& opts)
    : r_Opts(opts)
{
    m_Components.emplace_back(std::make_unique<ToggleOptionComponent>("90's Mode:", opts.enableAntialiasing));
    m_Components.emplace_back(std::make_unique<ToggleOptionComponent>("Rotary Knobs:", opts.rotary_knobs));
}

int OptionsListBoxModel::getNumRows() { return m_Components.size(); }
void OptionsListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected){}

juce::Component* OptionsListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
{
    if (rowNumber >= m_Components.size()) { return nullptr; }
    if (existingComponentToUpdate != nullptr) { return existingComponentToUpdate; }
    return m_Components[rowNumber].release();
}

OptionsComponent::OptionsComponent(GlobalOptions& opts)
    : m_Options(opts)
    , m_OptionsListBox("Options", nullptr)
{
    m_OptionsListBox.setModel(&m_Options);
    addAndMakeVisible(m_OptionsListBox);
}

void OptionsComponent::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromBottom(12);
    m_OptionsListBox.setBounds(bounds.reduced(2));
}

void OptionsComponent::paint(juce::Graphics& g)
{
    g.setColour(ER1Colours::lcdRed);
    g.fillAll();

    auto bounds = getLocalBounds();
    bounds.removeFromBottom(12);
    g.setColour(juce::Colours::red.darker());
    g.drawRect(bounds.reduced(1), 1);
}