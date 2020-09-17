//
// Created by Matt on 9/15/2020.
//

#include "SelectorButton.h"

#define STD_REDUCTION 2
#define BUTTON_RATIO 0.3f
#define MARGIN 5


SelectorButton::SelectorButton()
    : p_Selected(nullptr)
{}


SelectorButton::SelectorButton(std::vector<juce::Component*> icons)
    : m_Icons(std::move(icons))
{
    for (auto icon : m_Icons) { addAndMakeVisible(icon); }
    p_Selected = m_Icons[0];
}

void SelectorButton::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(STD_REDUCTION);
    const auto iconHeight = (bounds.getHeight() - (MARGIN * (m_Icons.size() + 1))) / m_Icons.size();

    bounds.removeFromTop(MARGIN);
    for (auto icon : m_Icons)
    {
        auto signalBounds = bounds.removeFromTop(iconHeight).removeFromLeft(iconHeight).reduced(STD_REDUCTION).toFloat();
        auto colour = getLookAndFeel().findColour(p_Selected == icon ? ColourIds::selectLitColour : ColourIds::selectUnlitColour);
        g.setColour(colour);
        g.fillEllipse(signalBounds);
        g.setColour(juce::Colours::black);
        g.drawEllipse(signalBounds, 1.0f);

        bounds.removeFromTop(MARGIN);
    }
}

void SelectorButton::resized()
{
    auto bounds = getLocalBounds().reduced(STD_REDUCTION);
    const auto iconHeight = (bounds.getHeight() - (MARGIN * (m_Icons.size() + 1))) / m_Icons.size();

    bounds.removeFromTop(MARGIN);

    for (auto icon : m_Icons)
    {
        auto iconBounds = bounds.removeFromTop(iconHeight);

        // Drop the indicator
        iconBounds.removeFromLeft(iconHeight + MARGIN).toFloat();

        icon->setBounds(iconBounds);

        bounds.removeFromTop(MARGIN);
    }
}


void SelectorButton::addIcon(juce::Component* component)
{
    m_Icons.push_back(component);
    addAndMakeVisible(component);
    p_Selected = m_Icons[0];
}
