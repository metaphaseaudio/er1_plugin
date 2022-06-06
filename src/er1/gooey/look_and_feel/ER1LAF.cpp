//
// Created by mzapp on 4/15/18.
//

#include "ER1LAF.h"
#include "ER1Colours.h"
#include "../widgets/LCDText.h"


using namespace juce;


ER1LAF::ER1LAF()
{
    setColour(juce::Label::textColourId, juce::Colours::black);
    setColour(ResizableWindow::ColourIds::backgroundColourId, ER1Colours::defaultBackground);

    setColour(SelectorButton::ColourIds::selectLitColour, juce::Colours::pink);
    setColour(SelectorButton::ColourIds::selectUnlitColour, juce::Colours::darkgrey);

    setColour(LCDText::ColourIds::bezelColour, ER1Colours::defaultForeground);
    setColour(LCDText::ColourIds::lcdColour, ER1Colours::lcdRed);
    setColour(LCDText::ColourIds::textColour, juce::Colours::red);
}


void ER1LAF::drawRotarySlider
(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
 const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider)
{
    auto outline   = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill      = slider.findColour(Slider::rotarySliderFillColourId);
    auto thumb     = slider.findColour(Slider::thumbColourId);

    if (!slider.isEnabled())
    {
        outline = outline.withSaturation(0.0f).withAlpha(0.5f);
        fill = fill.withSaturation(0.0f).withAlpha(0.5f);
        thumb = thumb.withSaturation(0.0f).withAlpha(0.5f);
    }

    auto bounds    = Rectangle<int>(x, y, width, height).toFloat().reduced(10);
    auto toAngle   = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto radius    = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

    const float dotIncrement = 0.5;

    Point<float> center(bounds.getCentreX(), bounds.getCentreY());
    auto knobBounds = Rectangle<float>(radius * 1.3f, radius * 1.3f).withCentre(center);

    auto shadow_centre = juce::Point<int>(x, y);
    shadow_centre.addXY(2, 2);
    auto circleShadow = juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 5, shadow_centre);
    juce::Path circle_path;
    circle_path.addEllipse(knobBounds);
    circleShadow.drawForPath(g, circle_path);

    g.setColour(fill);
    g.fillEllipse(knobBounds);

    if (radius > 0.0)
    {
        auto rotation = AffineTransform::rotation(0.0f, center.x, center.y);
        auto angle = rotaryStartAngle;

        while (angle < rotaryEndAngle)
        {
            auto dotPoint = center.getPointOnCircumference(radius, radius, angle)
                                  .transformedBy(rotation);

            auto dotBounds = Rectangle<float>(4, 4).withCentre(dotPoint);
            g.fillEllipse(dotBounds);
            angle += dotIncrement;
        }
    }

    g.setColour(outline);

    const auto halfPi = MathConstants<float>::halfPi;
    Point<float> thumbPoint(center.x + (radius / 1.25f) * std::cos(toAngle - halfPi)
                          , center.y + (radius / 1.25f) * std::sin(toAngle - halfPi));
    auto line = Line<float>(center, thumbPoint);

    shadow_centre = juce::Point<int>(x, y);
    shadow_centre.addXY(2, 2);
    auto lineShadow = juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 5, shadow_centre);
    juce::Path line_path;
    line_path.addLineSegment(line, 4);
    lineShadow.drawForPath(g, line_path);

    g.setColour(thumb);
    g.drawLine(line, 4);
}

void ER1LAF::drawKorgButton
(juce::Graphics &g, KorgButton &button, bool isMouseOverButton, bool isButtonDown)
{
    auto dwnColour = isMouseOverButton ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isMouseOverButton ? ER1Colours::padUpOver : ER1Colours::padUp;
    drawPad(g, button, isButtonDown ? dwnColour : upColour);
}

void ER1LAF::drawKorgToggleButton
(juce::Graphics &g, KorgToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
    auto toggleDown = button.getToggleState();
    auto dwnColour = isMouseOverButton ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isMouseOverButton ? ER1Colours::padUpOver : ER1Colours::padUp;
    drawPad(g, button, toggleDown ? dwnColour : upColour);
}

void ER1LAF::drawKorgPad(Graphics& g, juce::Component& pad, bool isPadLit, bool isPadDown)
{
    auto dwnColour = isPadLit ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isPadLit ? ER1Colours::padUpOver : ER1Colours::padUp;
    drawPad(g, pad, isPadDown ? dwnColour : upColour);
}

void ER1LAF::drawPad(Graphics& g, const juce::Component& area, const Colour& internalColour)
{
    auto bounds = area.getLocalBounds().reduced(5).toFloat();
    auto calcCurve = [](const juce::Rectangle<float>& area, int x) {
        return (std::min(area.getWidth(), area.getHeight()) * (1.0/std::sqrt(5))) / 2.0f;
    };
    auto curve = (std::min(area.getWidth(), area.getHeight()) * (1.0/std::sqrt(5))) / 2.0f;

    // Border
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(bounds, calcCurve(area.getLocalBounds().toFloat(), 5));

    // Shadow
    auto shadow_centre = area.getLocalBounds().getTopLeft();
    shadow_centre.addXY(1, 1);
    auto shadow = juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 1, shadow_centre.toInt());
    juce::Path button_path;
    button_path.addRoundedRectangle(bounds, curve);
    shadow.drawForPath(g, button_path);

    // Fill
    bounds = bounds.reduced(2);
    g.setColour(internalColour);
    g.fillRoundedRectangle(bounds, calcCurve(bounds, 5));

    // Highlight
    auto highlightBounds = bounds.reduced(2);
    g.setColour(internalColour.withMultipliedLightness(1.05));
    highlightBounds.setX(highlightBounds.getX() - 0.5);
    highlightBounds.setY(highlightBounds.getY() - 0.5);
    g.fillRoundedRectangle(highlightBounds, calcCurve(highlightBounds, 5));
}

