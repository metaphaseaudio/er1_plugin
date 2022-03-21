//
// Created by Matt on 9/19/2020.
//

#include "LCDText.h"
#include "../fonts/FontLCD.h"

LCDText::LCDText(const std::string& componentName, const std::string& text, int max_chars, float rotate_speed)
    : Label(componentName, LCDText::reformat(text))
    , m_MaxChars(max_chars > 0 ? max_chars : text.length())
    , m_RotateSpeed(rotate_speed)
    , m_Font(FontOption::standard)
    , m_Contrast(0.2)
    , m_Brightness(1.0)
{
    setFont(LCDText::getNewFont(m_Font));
    setJustificationType(juce::Justification::centred);
}

void LCDText::paint(juce::Graphics& g)
{
    const auto textColour =  getLookAndFeel().findColour(ColourIds::textColour);
    setColour(juce::Label::ColourIds::textColourId, textColour);
    setColour(juce::Label::ColourIds::textWhenEditingColourId, textColour);
//    m_LCDdark.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);//textColour.withAlpha(m_Contrast));

    // Draw background
    std::string fill;
    for (auto i = m_MaxChars; --i >= 0;) { fill += "~"; }

    juce::Path textPath;
    juce::GlyphArrangement glyphs;
    const auto localBounds = getLocalBounds();
    const auto font = Label::getFont();
    auto textArea = getBorderSize().subtractedFrom(localBounds);
    glyphs.addFittedText(
        font, fill,
        float(textArea.getX()), float(textArea.getY()), float(textArea.getWidth()), float(textArea.getHeight()),
        getJustificationType(), juce::jmax (1, (int) ((float) getHeight() / font.getHeight())), getMinimumHorizontalScale()
    );

    glyphs.createPath(textPath);
    g.setColour(textColour.withAlpha(m_Contrast));
    g.fillPath(textPath);

    auto shadow = juce::DropShadow(textColour, std::floor(getFont().getHeightInPoints() * 0.1), getLocalBounds().getTopLeft());
//    shadow.drawForPath(g, textPath);
    Label::paint(g);
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


void LCDText::setFontSize(int n)
{
    setFont(getFont().withPointHeight(n));
}

std::string LCDText::reformat(const std::string& x)
{
    std::string rv = x;
    std::replace(rv.begin(), rv.end(), ' ', '!');
    return rv;
}

void LCDText::setText(std::string& text, juce::NotificationType notify)
{
    Label::setText(reformat(text), notify);
}

