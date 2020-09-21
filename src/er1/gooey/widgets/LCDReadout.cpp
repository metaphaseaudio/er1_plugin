//
// Created by Matt on 9/19/2020.
//

#include "LCDReadout.h"
#include "../fonts/FontLCD.h"

LCDReadout::LCDReadout(size_t charCount, size_t fontSize, FontOption font, float contrast, float brightness, size_t bezelPx)
    : m_CharCount(charCount)
    , m_BezelThickness(bezelPx)
    , m_Contrast(contrast)
    , m_Brightness(brightness)
    , m_Font(font)
    , m_LCD("LCD")
    , m_LCDdark("LCD BG")
{
    addAndMakeVisible(m_LCDdark);
    addAndMakeVisible(m_LCD);
    m_LCD.setFont(LCDReadout::getFont(m_Font).withPointHeight(fontSize)); m_LCD.setJustificationType(juce::Justification::centred);
    m_LCDdark.setFont(LCDReadout::getFont(m_Font).withPointHeight(fontSize)); m_LCDdark.setJustificationType(juce::Justification::centred);
}

void LCDReadout::paint(juce::Graphics& g)
{
    m_LCD.setColour(juce::Label::ColourIds::textColourId, getLookAndFeel().findColour(ColourIds::textColour));
    m_LCDdark.setColour(juce::Label::ColourIds::textColourId, getLookAndFeel().findColour(ColourIds::textColour).withAlpha(m_Contrast));
    g.setColour(getLookAndFeel().findColour(ColourIds::bezelColour));
    g.fillRect(getLocalBounds());

    g.setColour(getLookAndFeel().findColour(ColourIds::lcdColour));
    g.fillRect(getLocalBounds().reduced(m_BezelThickness));

    g.setColour(getLookAndFeel().findColour(ColourIds::textColour).withAlpha(m_Contrast));

}

void LCDReadout::resized()
{
    const auto bounds = getLocalBounds();
    m_LCD.setBounds(bounds);
    m_LCDdark.setBounds(bounds);
}

const juce::Font& LCDReadout::getFont(LCDReadout::FontOption option)
{
    switch (option)
    {
        case standard: return FontLCD::ClassicRegular14();
        case italic: return FontLCD::ClassicItalic14();
        case light: return FontLCD::ClassicLight14();
        case lightItalic: return FontLCD::ClassicLightItalic14();
        case bold: return FontLCD::ClassicBold14();
        case boldItalic: return FontLCD::ClassicBoldItalic14();
    }
}

void LCDReadout::setText(const std::string& value)
{
    std::string fill;
    for (auto i = m_CharCount; --i >= 0;) { fill += "~"; }
    m_LCDdark.setText(fill, juce::NotificationType::dontSendNotification);
    m_LCD.setText(value, juce::NotificationType::dontSendNotification);

    repaint();
}
