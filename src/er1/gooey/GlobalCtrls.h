//
// Created by Mattb on 6/20/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../guts/MidiManager.h"
#include "patch_manager/PatchManager.h"
#include "widgets/KorgButton.h"
#include "../guts/ER1AudioProcessor.h"


class GlobalCtrls
    : public juce::Component
    , juce::Timer
    , juce::Button::Listener
{
public:
    GlobalCtrls(MidiManager& mgr, ER1AudioProcessor& proc);
    void resized() override;

private:
    void buttonClicked(juce::Button* btn) override;
    void timerCallback() override;
    MidiManager& r_MidiManager;
    PatchManager m_SoundPatchManager, m_BankPatchManager;
    juce::Label m_LiveModeLabel, m_NoteListenLabel, m_SelectSoundLabel, m_SelectBankLabel;
    KorgButton m_NoteListen;
    KorgToggleButton m_SelectSound, m_SelectBank, m_Options;
};
