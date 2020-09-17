//
// Created by mzapp on 4/15/18.
//

#include "ER1LAF.h"
#include "ER1Colours.h"
#include "../sound_edit_box/osc_section/WaveSelectors.h"


using namespace juce;


ER1LAF::ER1LAF()
{
    setColour(ResizableWindow::ColourIds::backgroundColourId, ER1Colours::defaultBackground);

    setColour(SelectorButton::ColourIds::selectLitColour, juce::Colours::pink);
    setColour(SelectorButton::ColourIds::selectUnlitColour, juce::Colours::darkgrey);

    setColour(WaveformComponent::ColourIds::waveformFGColour, juce::Colours::black);
    setColour(WaveformComponent::ColourIds::waveformBGColour, ER1Colours::defaultForeground);
}


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

void ER1LAF::drawKorgButton
(juce::Graphics &g, KorgButton &button, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(4);

    auto dwnColour = isMouseOverButton ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isMouseOverButton ? ER1Colours::padUpOver : ER1Colours::padUp;
    g.setColour(isButtonDown ? dwnColour : upColour);
    g.fillRoundedRectangle(bounds, 10);
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 10,2);
}

void
ER1LAF::drawKorgToggleButton
(juce::Graphics &g, KorgToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(4);
    auto toggleDown = button.getToggleState();

    auto dwnColour = isMouseOverButton ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isMouseOverButton ? ER1Colours::padUpOver : ER1Colours::padUp;
    g.setColour(isButtonDown || toggleDown ? dwnColour : upColour);
    g.fillRoundedRectangle(bounds, 10);
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 10,2);
}

void ER1LAF::drawKorgPad(Graphics& g, juce::Component& pad, bool isPadLit, bool isPadDown)
{
    auto bounds = pad.getLocalBounds().toFloat().reduced(4);
    auto dwnColour = isPadLit ? ER1Colours::padDwnOver : ER1Colours::padDwn;
    auto upColour = isPadLit ? ER1Colours::padUpOver : ER1Colours::padUp;
    g.setColour(isPadDown ? dwnColour : upColour);
    g.fillRoundedRectangle(bounds, 10);
    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(bounds, 10,2);
}

