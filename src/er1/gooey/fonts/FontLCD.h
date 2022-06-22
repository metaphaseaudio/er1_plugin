//
// Created by Matt on 9/19/2020.
//

#pragma once
#include "bin_data/FontDSEG7.h"
#include "bin_data/FontDSEG14.h"
#include "bin_data/Segment16C.h"
#include "bin_data/Arcade.h"
#include "bin_data/BitFonts.h"
#include <juce_gui_basics/juce_gui_basics.h>


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


    static const juce::Font& ClassicRegular16()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(Segment16C_Regular_ttf, Segment16C_Regular_ttfSize)));
        return font;
    }

    static const juce::Font& ClassicBold16()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(Segment16C_Bold_ttf, Segment16C_Bold_ttfSize)));
        return font;
    }

    static const juce::Font& ArcadeI()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(Arcade::ARCADE_I_TTF, Arcade::ARCADE_I_TTFSize)));
        return font;
    }

    static const juce::Font& ArcadeN()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(Arcade::ARCADE_N_TTF, Arcade::ARCADE_N_TTFSize)));
        return font;
    }


    static const juce::Font& EIGHT_BIT_WONDER_TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::EIGHT_BIT_WONDER_TTF,
                                                                                  BitFonts::EIGHT_BIT_WONDER_TTFSize)));
        return font;
    }
    static const juce::Font& editundo_ttf()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::editundo_ttf, BitFonts::editundo_ttfSize)));
        return font;
    }
    static const juce::Font& Minecraft_ttf()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::Minecraft_ttf, BitFonts::Minecraft_ttfSize)));
        return font;
    }
    static const juce::Font& Retro_Gaming_ttf()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::Retro_Gaming_ttf, BitFonts::Retro_Gaming_ttfSize)));
        return font;
    }
    static const juce::Font& ROTORB___TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::ROTORB___TTF, BitFonts::ROTORB___TTFSize)));
        return font;
    }
    static const juce::Font& ROTORCAP_TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::ROTORCAP_TTF, BitFonts::ROTORCAP_TTFSize)));
        return font;
    }
    static const juce::Font& ROTOREB__TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::ROTOREB__TTF, BitFonts::ROTOREB__TTFSize)));
        return font;
    }
    static const juce::Font& ROTORE___TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::ROTORE___TTF, BitFonts::ROTORE___TTFSize)));
        return font;
    }
    static const juce::Font& ROTORS___TTF()
    {
        static juce::Font font(juce::Font(juce::Typeface::createSystemTypefaceFor(BitFonts::ROTORS___TTF, BitFonts::ROTORS___TTFSize)));
        return font;
    }

}


