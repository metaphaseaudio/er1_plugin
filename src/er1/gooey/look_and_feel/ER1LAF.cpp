//
// Created by mzapp on 4/15/18.
//

#include "ER1LAF.h"
#include "ER1Colours.h"
#include "../widgets/LCDText.h"
#include "../fonts/FontLCD.h"
#include "meta/util/math.h"


using namespace juce;


static std::unique_ptr<Drawable> createDrawableFromSVG (const char* data)
{
    auto xml = parseXML (data);
    jassert (xml != nullptr);
    return Drawable::createFromSVG (*xml);
}

ER1LAF::ER1LAF()
    : m_LCDFilter(new juce::GlowEffect())
{
    setColour(juce::Label::textColourId, juce::Colours::black);
    setColour(ResizableWindow::ColourIds::backgroundColourId, ER1Colours::defaultBackground);

    setColour(LCDText::ColourIds::bezelColour, ER1Colours::defaultForeground);
    setColour(LCDText::ColourIds::lcdColour, ER1Colours::lcdRed);
    setColour(LCDText::ColourIds::textColour, juce::Colours::red.withAlpha(0.5f));

    setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::ListBox::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    setColour(juce::ListBox::ColourIds::textColourId, findColour(LCDText::ColourIds::textColour));

    setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::Label::ColourIds::textColourId, findColour(LCDText::ColourIds::textColour));

    setColour(juce::ComboBox::ColourIds::arrowColourId, findColour(LCDText::ColourIds::textColour));
    setColour(juce::ComboBox::ColourIds::textColourId, findColour(LCDText::ColourIds::textColour));

    dynamic_cast<juce::GlowEffect*>(m_LCDFilter.get())->
            setGlowProperties(2, findColour(LCDText::ColourIds::textColour), juce::Point<int>(0, 0));
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

const WidgetManager::WidgetInfo&
ER1LAF::getWidgetInfo(WidgetManager::WidgetID widget_id, WidgetManager::WidgetVariant variant, int index) const
{ return m_Widgets.getWidgetInfo(widget_id, variant, index); }

void ER1LAF::drawComboBox
(Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
{
    juce::Rectangle<int> arrowZone(width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour(box.findColour(ComboBox::arrowColourId));
    g.strokePath(path, PathStrokeType (2.0f));
}


void ER1LAF::drawToggleButton(juce::Graphics& g, juce::ToggleButton& btn, bool isHighlighted, bool isDown)
{
    const auto lineWidth = 1;
    const auto toggleColour = btn.getToggleState() ? juce::Colours::red : juce::Colours::red.darker(0.6);

    const auto localBounds = btn.getLocalBounds().reduced(1);
    g.setColour(isHighlighted ? toggleColour.brighter() : toggleColour);
    g.drawRect(btn.getLocalBounds(), lineWidth);

    g.setColour(toggleColour);
    g.setFont(FontLCD::defaultFont().withPointHeight(9));

    if (btn.getToggleState())
    {
        const auto indicatorBounds = localBounds.withX(localBounds.getX() + 1);
        g.drawFittedText("x", indicatorBounds, juce::Justification::centred, 1);
    }
}

Font ER1LAF::getLabelFont(Label& label)
{
    const auto font = label.getFont();
    return FontLCD::defaultFont().withPointHeight(font.getHeightInPoints());
}

