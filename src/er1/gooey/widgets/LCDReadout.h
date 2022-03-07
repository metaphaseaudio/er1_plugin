//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LCDReadout
    : public juce::Component
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

    LCDReadout(size_t char_count, size_t font_size, FontOption font=standard, float contrast=0.2, float brightness=1.0, size_t bezelPx=2);
    void setText(const std::string& value);
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    static const juce::Font& getFont(FontOption option);

    int m_CharCount, m_BezelThickness;
    float m_Contrast, m_Brightness;
    FontOption m_Font;
    juce::Label m_LCD, m_LCDdark;
};


