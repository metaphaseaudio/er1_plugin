//
// Created by mzapp on 4/15/18.
//

#include "ER1LAF.h"
#include "ER1Colours.h"
#include "../widgets/LCDText.h"
#include "../fonts/FontLCD.h"


using namespace juce;

static std::unique_ptr<Drawable> createDrawableFromSVG (const char* data)
{
    auto xml = parseXML (data);
    jassert (xml != nullptr);
    return Drawable::createFromSVG (*xml);
}

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

void ER1LAF::drawFileBrowserRow(Graphics& g, int width, int height, const File& file, const String& filename, juce::Image* icon,
                                const String& fileSizeDescription, const String& fileTimeDescription, bool isDirectory, bool isItemSelected,
                                int itemIndex, DirectoryContentsDisplayComponent& dcc)
{
    auto fileListComp = dynamic_cast<Component*> (&dcc);

    if (isItemSelected)
        g.fillAll (fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightColourId)
                                           : findColour (DirectoryContentsDisplayComponent::highlightColourId));

    const int x = 32;
    g.setColour (Colours::black);


    if (auto* d = isDirectory ? getDefaultFolderImage() : getDefaultDocumentFileImage())
        d->drawWithin(g, Rectangle<float> (0, 0, height, (float) height),
        RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);

    if (isItemSelected)
        g.setColour(fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::highlightedTextColourId)
                                            : findColour (DirectoryContentsDisplayComponent::highlightedTextColourId));
    else
        g.setColour(fileListComp != nullptr ? fileListComp->findColour (DirectoryContentsDisplayComponent::textColourId)
                                            : findColour (DirectoryContentsDisplayComponent::textColourId));

    g.setFont(FontLCD::defaultFont());
    g.setFont ((float) height * 0.7f);

    if (width > 450 && !isDirectory)
    {
        auto sizeX = roundToInt ((float) width * 0.7f);
        auto dateX = roundToInt ((float) width * 0.8f);

        g.drawFittedText(filename, height, 0, sizeX - x, height, Justification::centredLeft, 1);

        g.setFont ((float) height * 0.5f);
        g.setColour (Colours::darkgrey);

        if (!isDirectory)
        {
            g.drawFittedText(fileSizeDescription, sizeX, 0, dateX - sizeX - 8, height, Justification::centredRight, 1);
            g.drawFittedText(fileTimeDescription, dateX, 0, width - 8 - dateX, height, Justification::centredRight, 1);
        }
    }
    else
    {
        g.drawFittedText(filename, height, 0, width - x, height, Justification::centredLeft, 1);
    }
}

const juce::Drawable* ER1LAF::getDefaultDocumentFileImage()
{
    if (documentImage == nullptr)
    {
        documentImage = createDrawableFromSVG(R"svgdata(

<svg
   width="32"
   height="32"
   viewBox="0 0 8.4666665 8.4666666"
   version="1.1"
   id="svg5"
   xml:space="preserve"
   inkscape:version="1.2 (dc2aedaf03, 2022-05-15)"
   sodipodi:docname="doc_icon.svg"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg"><sodipodi:namedview
     id="namedview7"
     pagecolor="#505050"
     bordercolor="#eeeeee"
     borderopacity="1"
     inkscape:showpageshadow="0"
     inkscape:pageopacity="0"
     inkscape:pagecheckerboard="0"
     inkscape:deskcolor="#505050"
     inkscape:document-units="mm"
     showgrid="true"
     showguides="true"
     inkscape:zoom="22.853691"
     inkscape:cx="12.886321"
     inkscape:cy="14.461559"
     inkscape:window-width="1687"
     inkscape:window-height="1408"
     inkscape:window-x="1744"
     inkscape:window-y="0"
     inkscape:window-maximized="0"
     inkscape:current-layer="layer1"><inkscape:grid
       type="xygrid"
       id="grid426"
       empspacing="4"
       visible="true" /></sodipodi:namedview><defs
     id="defs2" /><g
     inkscape:label="Layer 1"
     inkscape:groupmode="layer"
     id="layer1"><rect
       style="fill:#ffffff;stroke-width:0.305514"
       id="rect699"
       width="1.0583334"
       height="8.4666662"
       x="0.79374999"
       y="0" /><rect
       style="fill:#ffffff;stroke-width:0.305514"
       id="rect701"
       width="5.8208332"
       height="1.058333"
       x="1.5875"
       y="7.4083333" /><rect
       style="fill:#ffffff;stroke-width:0.305514"
       id="rect703"
       width="1.058333"
       height="4.4979167"
       x="6.3499999"
       y="3.175" /><rect
       style="fill:#ffffff;stroke-width:0.352777"
       id="rect707"
       width="1.0583338"
       height="1.0583334"
       x="5.2916665"
       y="2.1166666" /><rect
       style="fill:#ffffff;stroke-width:0.352777"
       id="rect709"
       width="1.0583335"
       height="1.0583334"
       x="4.2333331"
       y="1.0583332" /><rect
       style="fill:#ffffff;stroke-width:0.365159"
       id="rect713"
       width="2.6458333"
       height="1.0583333"
       x="1.5875"
       y="0" /><rect
       style="fill:#ffffff;stroke-width:0.305514"
       id="rect715"
       width="1.0583333"
       height="2.9104166"
       x="2.6458333"
       y="0.79374999" /><rect
       style="fill:#ffffff;stroke-width:0.316237"
       id="rect717"
       width="3.96875"
       height="1.0583333"
       x="2.6458333"
       y="3.7041667" /></g></svg>
)svgdata");
    }

    documentImage->replaceColour(juce::Colours::white, juce::Colours::red);
    return documentImage.get();
}

const juce::Drawable* ER1LAF::getDefaultFolderImage()
{
    if (folderImage == nullptr)
    {
        folderImage = createDrawableFromSVG(R"svgdata(
<svg
   width="32"
   height="32"
   viewBox="0 0 8.4666665 8.4666666"
   version="1.1"
   id="svg5"
   xml:space="preserve"
   inkscape:version="1.2 (dc2aedaf03, 2022-05-15)"
   sodipodi:docname="folder_icon.svg"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg"><sodipodi:namedview
     id="namedview7"
     pagecolor="#505050"
     bordercolor="#eeeeee"
     borderopacity="1"
     inkscape:showpageshadow="0"
     inkscape:pageopacity="0"
     inkscape:pagecheckerboard="0"
     inkscape:deskcolor="#505050"
     inkscape:document-units="mm"
     showgrid="true"
     showguides="true"
     inkscape:zoom="22.853691"
     inkscape:cx="12.842564"
     inkscape:cy="14.395924"
     inkscape:window-width="3378"
     inkscape:window-height="1417"
     inkscape:window-x="54"
     inkscape:window-y="-8"
     inkscape:window-maximized="1"
     inkscape:current-layer="layer1"><inkscape:grid
       type="xygrid"
       id="grid426"
       empspacing="4"
       visible="true" /></sodipodi:namedview><defs
     id="defs2" /><g
     inkscape:label="Layer 1"
     inkscape:groupmode="layer"
     id="layer1"><rect
       style="fill:#ffffff;stroke-width:0.274881"
       id="rect480"
       width="8.4666662"
       height="4.4979167"
       x="1.5894571e-08"
       y="2.9104166" /><rect
       style="fill:#ffffff;stroke-width:0.285783"
       id="rect482"
       width="7.4083333"
       height="0.52916664"
       x="0.52916664"
       y="1.8520834" /><rect
       style="fill:#ffffff;stroke-width:0.476983"
       id="rect492"
       width="3.4395833"
       height="0.79375011"
       x="0.52916664"
       y="1.0583333" /></g></svg>
)svgdata");
    }

    folderImage->replaceColour(juce::Colours::white, juce::Colours::red);
    return folderImage.get();
}

void ER1LAF::drawScrollbar(Graphics& g, ScrollBar& bar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition,
                           int thumbSize, bool isMouseOver, bool isMouseDown)
{
    ignoreUnused (isMouseDown);

    Rectangle<int> thumbBounds;

    if (isScrollbarVertical)
        thumbBounds = { x, thumbStartPosition, width, thumbSize };
    else
        thumbBounds = { thumbStartPosition, y, thumbSize, height };

    auto c = juce::Colours::red;
    g.setColour (isMouseOver ? c.brighter (0.25f) : c);
    g.fillRect(thumbBounds.reduced (1).toFloat());
}

void ER1LAF::drawTextEditorOutline(Graphics&, int width, int height, TextEditor&) {}

void ER1LAF::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));

        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);

        auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          1.0f);

        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}
