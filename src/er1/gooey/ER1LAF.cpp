//
// Created by mzapp on 4/15/18.
//

#include "ER1LAF.h"

using namespace juce;

void ER1LAF::drawRotarySlider
(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
 const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider &slider)
{
    auto outline   = slider.findColour(Slider::rotarySliderOutlineColourId);
    auto fill      = slider.findColour(Slider::rotarySliderFillColourId);
    auto bounds    = Rectangle<int>(x, y, width, height).toFloat().reduced(10);
    auto toAngle   = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto radius    = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

    const float dotIncrement = 0.5;

    Point<float> center(bounds.getCentreX(), bounds.getCentreY());
    auto knobBounds = Rectangle<float>(radius * 1.3f, radius * 1.3f).withCentre(center);

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

    auto thumbWidth = 8.0f * 2.0f;
    const auto halfPi = MathConstants<float>::halfPi;
    Point<float> thumbPoint(center.x + (radius / 1.25f) * std::cos(toAngle - halfPi)
                          , center.y + (radius / 1.25f) * std::sin(toAngle - halfPi));
    g.setColour (slider.findColour (Slider::thumbColourId));
    auto line = Line<float>(center, thumbPoint);
    g.drawLine(line, 4);
}
