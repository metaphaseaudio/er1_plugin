//
// Created by Matt on 6/10/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>


namespace Arrow
{
    class UpAndRight
        : public juce::Component
    {
    public:
        explicit UpAndRight(bool mirrored=false);
        void paint(juce::Graphics& g) override;

    private:
        bool m_Mirrored;
    };

    class RightAndDown
        : public juce::Component
    {
    public:
        void paint(juce::Graphics& g) override;
    };

}

