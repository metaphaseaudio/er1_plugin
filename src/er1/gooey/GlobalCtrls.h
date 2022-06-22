//
// Created by Mattb on 6/20/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../guts/MidiManager.h"
#include "widgets/KorgButton.h"


class GlobalCtrls
    : public juce::Component
    , juce::Timer
    , juce::Button::Listener
{
public:
    explicit GlobalCtrls(MidiManager& mgr);
    void resized() override;

private:
    void buttonClicked(juce::Button* btn) override;
    void timerCallback() override;
    MidiManager& r_MidiManager;
    juce::Label m_LiveModeLabel, m_NoteListenLabel, m_SelectSoundLabel, m_SelectBankLabel;
    KorgButton m_LiveMode, m_NoteListen, m_SelectSound, m_SelectBank;
};
