//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../widgets/KorgButton.h"
#include "../widgets/KorgPad.h"
#include "../widgets/SelectorButton.h"
#include "WidgetManager.h"


class ER1LAF
    : public juce::LookAndFeel_V4
{
public:
    ER1LAF();

    void drawRotarySlider
    (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
     const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawKorgPad(juce::Graphics& g, juce::Component& pad, bool isPadLit, bool isPadDown, float brightnessAdjust=0.0f);

    void drawKorgButton
    (juce::Graphics& g, KorgButton& button, bool isMouseOverButton, bool isButtonDown);

    void drawKorgToggleButton
        (juce::Graphics& g, KorgToggleButton& button, bool isMouseOverButton, bool isButtonDown);

    void drawFileBrowserRow(
        juce::Graphics&, int width, int height,
        const juce::File& file, const juce::String& filename, juce::Image* icon,
        const juce::String& fileSizeDescription, const juce::String& fileTimeDescription,
        bool isDirectory, bool isItemSelected, int itemIndex,
        juce::DirectoryContentsDisplayComponent&
    ) override;

    const juce::Drawable* getDefaultDocumentFileImage() override;
    const juce::Drawable* getDefaultFolderImage() override;

    void drawScrollbar(juce::Graphics& graphics, juce::ScrollBar& bar, int x, int y, int width, int height, bool isScrollbarVertical,
                       int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

    void drawLabel(juce::Graphics& g, juce::Label& l) override;
    void drawTextEditorOutline(juce::Graphics&, int width, int height, juce::TextEditor&) override;

    [[nodiscard]] const WidgetManager::WidgetInfo& getWidgetInfo(
            WidgetManager::WidgetID widget_id, WidgetManager::WidgetVariant variant, int index) const;


private:
    std::unique_ptr<juce::Drawable> folderImage, documentImage;
    WidgetManager m_Widgets;

    void drawPad(juce::Graphics& g, const juce::Component& area, const juce::Colour& internalColour);
};

class LCDLAF
    : public ER1LAF
{
public:
    LCDLAF();
    [[nodiscard]] juce::ImageEffectFilter* getLCDFilter() const { return m_LCDFilter.get(); };
    juce::Font getLabelFont(juce::Label& label) override;
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& btn, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    std::unique_ptr<juce::ImageEffectFilter> m_LCDFilter;
};
