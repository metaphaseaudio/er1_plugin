//
// Created by Matt on 1/13/2021.
//

#include "KorgComboBox.h"

KorgComboBox::KorgComboBox(juce::AudioParameterChoice& param)
    : meta::TimedParameterListener(param)
{
    auto choices = param.getAllValueStrings();
    for (int i = 0; i < choices.size(); i++)
        { addItem(choices[i], i + 1); }
    setSelectedId(param.getIndex() + 1, juce::dontSendNotification);
    param.addListener(this);
    addListener(this);
}

void KorgComboBox::handleNewParameterValue()
{
    auto p_index = static_cast<juce::AudioParameterChoice&>(r_Parameter).getIndex() + 1;
    auto s_index = getSelectedId();
    if (p_index != s_index)
        { setSelectedId(p_index); }
}

void KorgComboBox::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (getParameter().getCurrentValueAsText() != getText())
    {
        getParameter().beginChangeGesture();
        getParameter().setValueNotifyingHost(r_Parameter.getValueForText(getText()));
        getParameter().endChangeGesture();
    }
}
