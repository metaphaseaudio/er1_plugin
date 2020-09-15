//
// Created by Matt on 9/15/2020.
//

#include "SelectorButton.h"

#define STD_REDUCTION 2
#define BUTTON_RATIO 0.3f
#define MARGIN 5

SelectorButton::SelectorButton(const std::initializer_list<juce::Component*>& icons)
    : m_Next("Next")
    , m_Icons(icons)
{}

void SelectorButton::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(STD_REDUCTION);
    const auto iconHeight = (bounds.getHeight() - (MARGIN * m_Icons.size())) / m_Icons.size();

    // Abandon the button, and first margin
    bounds.removeFromLeft((bounds.getWidth() * BUTTON_RATIO) + MARGIN);

    for (auto icon : m_Icons)
    {
        bounds.removeFromTop(MARGIN);
        auto signalBounds = bounds.removeFromTop(iconHeight).removeFromLeft(iconHeight).toFloat();
        auto colour = getLookAndFeel().findColour(p_Selected == icon ? ColourIds::selectLitColour : ColourIds::selectUnlitColour);
        g.fillEllipse(signalBounds);
        g.drawEllipse(signalBounds, 1.0f);
    }
}

void SelectorButton::resized()
{
    auto bounds = getLocalBounds().reduced(STD_REDUCTION);
    const auto iconHeight = (bounds.getHeight() - (MARGIN * m_Icons.size())) / m_Icons.size();

    m_Next.setBounds(bounds.removeFromLeft((bounds.getWidth() * BUTTON_RATIO)));
    bounds.removeFromLeft(MARGIN);

    for (auto icon : m_Icons)
    {
        bounds.removeFromTop(MARGIN);
        auto iconBounds = bounds.removeFromTop(iconHeight);

        // Drop the indicator
        iconBounds.removeFromLeft(iconHeight + MARGIN).toFloat();

        icon->setBounds(iconBounds);

        bounds.removeFromTop(MARGIN);
    }
}
