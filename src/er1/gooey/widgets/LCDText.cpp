//
// Created by Matt on 9/19/2020.
//

#include "LCDText.h"
#include "../fonts/FontLCD.h"


LCDText::LCDText(const std::string& componentName, const juce::String& text, float rotate_speed)
    : Label(componentName, text)
    , m_RotateSpeed(rotate_speed)
{

    setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::transparentBlack);
    this->onEditorShow = [this]
    {
        auto* editor = getCurrentTextEditor();
        auto editorFont = editor->getFont();
        editor->setJustification(this->getJustificationType());
        editor->setFont (editorFont);

        auto bounds = getLocalBounds();
        bounds.setHeight(bounds.getHeight() + 2);
        auto localPosition = bounds.getTopLeft();
        localPosition.addXY(0, -3);
        editor->setBounds(bounds);
        editor->setTopLeftPosition(localPosition);
        editor->repaint();
    };
}


void LCDText::timerCallback(){}

juce::TextEditor* LCDText::createEditorComponent()
{
    return Label::createEditorComponent();
}

