//
// Created by Matt on 9/19/2020.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class LCDText
    : public juce::Label
    , juce::Timer
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

    LCDText(const std::string& componentName, const juce::String& text, int max_chars, float rotate_speed=0.5);

    void setFontSize(int n);

    void setContrast(float contrast);
    void setBrightness(float brightness);

    void paint(juce::Graphics& g) override;
    void setText(const std::string& text, juce::NotificationType notify);
    void timerCallback() override;

private:
    static juce::String reformat(const juce::String& x);
    static const juce::Font& getNewFont(FontOption option);

    std::string m_Text;
    int m_MaxChars;
    float m_Contrast, m_Brightness, m_RotateSpeed;
    FontOption m_Font;
};


