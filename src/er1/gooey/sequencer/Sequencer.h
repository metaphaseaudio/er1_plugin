//
// Created by mzapp on 4/16/18.
//

#include <JuceHeader.h>
#include "SequencerButton.h"

#define SEQUENCER_BUTTON_COUNT 16
#define SEQUENCER_STEP_COUNT 64

class Sequencer
    : public juce::Component
    , juce::Button::Listener
{
public:
    Sequencer();
    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button*) override;

private:
    std::vector<std::unique_ptr<SequencerButton>> m_SequencerButtons;
    juce::BigInteger m_Sequence;
};
