//
// Created by Matt on 9/19/2020.
//

#include "LCDText.h"
#include "../fonts/FontLCD.h"

LCDText::LCDText(const std::string& componentName, const std::string& text)
    : Label(componentName, text)
    , m_LCDdark(componentName + "_BG")
    , m_CharCount(text.length())
    , m_Font(FontOption::standard)
    , m_Contrast(0.2)
    , m_Brightness(1.0)
{
    addAndMakeVisible(m_LCDdark);
    setFont(LCDText::getNewFont(m_Font));
    setJustificationType(juce::Justification::centred);
    m_LCDdark.setFont(LCDText::getNewFont(m_Font)); m_LCDdark.setJustificationType(juce::Justification::centred);

}


void LCDText::paint(juce::Graphics& g)
{
    const auto textColour =  getLookAndFeel().findColour(ColourIds::textColour);
    setColour(juce::Label::ColourIds::textColourId, textColour);
    setColour(juce::Label::ColourIds::textWhenEditingColourId, textColour);
    m_LCDdark.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);//textColour.withAlpha(m_Contrast));

    juce::Path textPath;
    juce::GlyphArrangement glyphs;
    const auto localBounds = getLocalBounds();

    const auto font = Label::getFont();
    auto textArea = getBorderSize().subtractedFrom(localBounds);
    glyphs.addFittedText(
        font, getText(),
        float(textArea.getX()), float(textArea.getY()), float(textArea.getWidth()), float(textArea.getHeight()),
        getJustificationType(), juce::jmax (1, (int) ((float) getHeight() / font.getHeight())), getMinimumHorizontalScale()
    );

    glyphs.createPath(textPath);

    auto shadow = juce::DropShadow(textColour, std::floor(getFont().getHeightInPoints() * 0.1), getLocalBounds().getTopLeft());
    shadow.drawForPath(g, textPath);
    Label::paint(g);
}

void LCDText::resized()
{
    Label::resized();
    m_LCDdark.setBounds(getLocalBounds());
}

const juce::Font& LCDText::getNewFont(LCDText::FontOption option)
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

void LCDText::setText(const std::string& value)
{
    std::string fill;
    for (auto i = m_CharCount; --i >= 0;) { fill += "~"; }
    m_LCDdark.setText(fill, juce::NotificationType::dontSendNotification);
    Label::setText(value, juce::NotificationType::dontSendNotification);

    repaint();
}

void LCDText::setFontSize(int n)
{
    setFont(getFont().withPointHeight(n));
}

