//
// Created by Mattb on 6/9/2022.
//

#include "ConfigSectionComponent.h"
#include "../../Images.h"
#include "../../look_and_feel/ER1Colours.h"
#include "../../look_and_feel/StandardShapes.h"


ConfigSectionComponent::ConfigSectionComponent(ER1SoundPatch& params)
    : m_Screen(params)
{ addAndMakeVisible(m_Screen); }

void ConfigSectionComponent::resized()
{
    auto bounds = getLocalBounds().reduced(5);
    auto button = StandardShapes::smallSquareButton;
    bounds.removeFromBottom(button.getHeight());
    m_Screen.setBounds(bounds);
}

void ConfigSectionComponent::paint(juce::Graphics& g)
{
    g.setColour(ER1Colours::defaultBackground);
    g.fillAll();
    auto redBounds = getLocalBounds().reduced(2);
    g.reduceClipRegion(redBounds);
    juce::Image bg = juce::ImageCache::getFromMemory(Images::red_bg_png, Images::red_bg_pngSize);
    g.drawImage(bg, getLocalBounds().toFloat());
}
