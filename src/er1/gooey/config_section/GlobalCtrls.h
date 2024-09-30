//
// Created by Mattb on 6/20/2022.
//

#pragma once
#include "juce_gui_basics/juce_gui_basics.h"
#include "../../guts/MidiManager.h"
#include "../PatchManager.h"
#include "../widgets/KorgButton.h"
#include "../widgets/LCDText.h"
#include "../../guts/ER1AudioProcessor.h"
#include "../Options.h"
#include "../look_and_feel/ER1LAF.h"
#include "LCDScreen.h"


class GlobalCtrls
    : public juce::Component
    , public juce::ChangeBroadcaster
    , juce::Timer
    , juce::Button::Listener
    , juce::ChangeListener
{
public:
    GlobalCtrls(MidiManager& mgr, ER1AudioProcessor& proc);
    ~GlobalCtrls() override;
    void resized() override;

    void setVoice(const ER1SoundPatch::Ptr& patch);

    juce::File getCurrentSoundFolder() const { return m_SoundPatchManager.getCurrentDirectory(); }
    juce::File getCurrentBankFolder() const { return m_BankPatchManager.getCurrentDirectory(); }
    void setCurrentSoundFolder(const juce::File& dir) { m_SoundPatchManager.changeDir(dir); repaint(); }
    void setCurrentBankFolder(const juce::File& dir) { m_BankPatchManager.changeDir(dir); repaint(); }

    void setBankName(const std::string& name);

private:
    void buttonClicked(juce::Button* btn) override;
    void timerCallback() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

    MidiManager& r_MidiManager;
    PatchManager m_SoundPatchManager, m_BankPatchManager;
    OptionsComponent m_OptionsManager;
    LCDScreen m_LCDScreen;
    LCDText m_Bank;
    juce::Label m_BankLabel;
    KorgToggleButton m_NoteListen, m_SelectSound, m_SelectBank, m_Options;
};
