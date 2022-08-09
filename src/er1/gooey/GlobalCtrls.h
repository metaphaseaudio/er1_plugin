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
#include "Options.h"
#include "look_and_feel/ER1LAF.h"


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

    void setVoice(JSONPatch* patch) { m_SoundPatchManager.changeTarget(patch); }

private:
    void buttonClicked(juce::Button* btn) override;
    void timerCallback() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

    LCDLAF m_LCDLAF;
    MidiManager& r_MidiManager;
    PatchManager m_SoundPatchManager, m_BankPatchManager;
    OptionsComponent m_OptionsManager;
    LCDText m_Bank;
    juce::Label m_LiveModeLabel, m_NoteListenLabel, m_SelectSoundLabel, m_SelectBankLabel, m_BankLabel;
    KorgToggleButton m_NoteListen, m_SelectSound, m_SelectBank, m_Options;
};
