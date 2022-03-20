//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LCDText
    : public juce::Label
{
public:
    enum ColourIds
    {
        textColour = 0x1022CD1,
        lcdColour = 0x1022CD2,
        bezelColour = 0x1022CD3
    };

    enum FontOption
    {
        standard,
        italic,
        light,
        lightItalic,
        bold,
        boldItalic
    };

    LCDText(const std::string& componentName, const std::string& text="");

//    void setCharCount(int n);
    void setFontSize(int n);
//    void setFontOption(FontOption font);
//    void setContrast(float contrast);
//    void setBrightness(float brightness);

    void setText(const std::string& value);
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    static const juce::Font& getNewFont(FontOption option);

    int m_CharCount;
    float m_Contrast, m_Brightness;
    FontOption m_Font;
    juce::Label m_LCDdark;
};


