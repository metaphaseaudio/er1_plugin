//
// Created by Mattb on 6/20/2022.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../guts/MidiManager.h"
#include "patch_manager/PatchManager.h"
#include "widgets/KorgButton.h"
#include "widgets/LCDText.h"
#include "../guts/ER1AudioProcessor.h"


class GlobalCtrls
    : public juce::Component
    , public juce::ChangeBroadcaster
    , juce::Timer
    , juce::Button::Listener
    , juce::ChangeListener
{
public:
    GlobalCtrls(MidiManager& mgr, ER1AudioProcessor& proc);
    void resized() override;

private:
    void buttonClicked(juce::Button* btn) override;
    void timerCallback() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

    MidiManager& r_MidiManager;
    PatchManager m_SoundPatchManager, m_BankPatchManager;
    LCDText m_Bank;
    juce::Label m_LiveModeLabel, m_NoteListenLabel, m_SelectSoundLabel, m_SelectBankLabel, m_BankLabel;
    KorgButton m_NoteListen;
    KorgToggleButton m_SelectSound, m_SelectBank, m_Options;
};
