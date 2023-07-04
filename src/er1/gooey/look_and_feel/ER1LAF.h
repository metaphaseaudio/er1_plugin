//
// Created by mzapp on 4/15/18.
//
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "WidgetManager.h"


class ER1LAF
    : public juce::LookAndFeel_V4
{
public:
    ER1LAF();

    void drawFileBrowserRow(
        juce::Graphics&, int width, int height,
        const juce::File& file, const juce::String& filename, juce::Image* icon,
        const juce::String& fileSizeDescription, const juce::String& fileTimeDescription,
        bool isDirectory, bool isItemSelected, int itemIndex,
        juce::DirectoryContentsDisplayComponent&
    ) override;

    juce::Font getLabelFont(juce::Label& label) override;

    void drawComboBox(
            juce::Graphics& g, int width, int height, bool isButtonDown,
            int buttonX, int buttonY, int buttonW, int buttonH,
            juce::ComboBox& box
    ) override;

    const juce::Drawable* getDefaultDocumentFileImage() override;
    const juce::Drawable* getDefaultFolderImage() override;

    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& btn, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void drawScrollbar(juce::Graphics& graphics, juce::ScrollBar& bar, int x, int y, int width, int height, bool isScrollbarVertical,
                       int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

    void drawLabel(juce::Graphics& g, juce::Label& l) override;
    void drawTextEditorOutline(juce::Graphics&, int width, int height, juce::TextEditor&) override;

    [[nodiscard]] const WidgetManager::WidgetInfo& getWidgetInfo(
            WidgetManager::WidgetID widget_id, WidgetManager::WidgetVariant variant, int index) const;

    [[nodiscard]] juce::ImageEffectFilter* getLCDFilter() const { return m_LCDFilter.get(); };

private:
    std::unique_ptr<juce::Drawable> folderImage, documentImage;

    WidgetManager m_Widgets;

    std::unique_ptr<juce::ImageEffectFilter> m_LCDFilter;
};
