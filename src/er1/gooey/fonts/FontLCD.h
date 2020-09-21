//
// Created by Matt on 9/19/2020.
//

#pragma once
#include "bin_data/FontDSEG7.h"
#include "bin_data/FontDSEG14.h"
#include <JuceHeader.h>


namespace FontLCD
{
    static const juce::Font& ClassicBold7()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicBold_ttf, DSEG7ClassicBold_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicBoldItalic7()
    {

        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicBoldItalic_ttf, DSEG7ClassicBoldItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicItalic7()
    {

        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicItalic_ttf, DSEG7ClassicItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicLight7()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicLight_ttf, DSEG7ClassicLight_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicLightItalic7()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicLightItalic_ttf, DSEG7ClassicLightItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicRegular7()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG7ClassicRegular_ttf, DSEG7ClassicRegular_ttfSize)));
        return font;
    }

    static const juce::Font& ClassicBold14()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicBold_ttf, DSEG14ClassicBold_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicBoldItalic14()
    {

        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicBoldItalic_ttf, DSEG14ClassicBoldItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicItalic14()
    {

        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicItalic_ttf, DSEG14ClassicItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicLight14()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicLight_ttf, DSEG14ClassicLight_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicLightItalic14()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicLightItalic_ttf, DSEG14ClassicLightItalic_ttfSize)));
        return font;
    }


    static const juce::Font& ClassicRegular14()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(DSEG14ClassicRegular_ttf, DSEG14ClassicRegular_ttfSize)));
        return font;
    }
}


