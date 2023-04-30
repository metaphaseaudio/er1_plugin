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
    auto bounds = getLocalBounds();
    bounds.removeFromTop(50);
    bounds.removeFromLeft(108);
    bounds = bounds.removeFromTop(93);
    bounds = bounds.removeFromLeft(286);
    m_Screen.setBounds(bounds);
}
