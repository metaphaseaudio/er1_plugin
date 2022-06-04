//
// Created by Matt on 1/13/2021.
//

#include "KorgComboBox.h"

KorgComboBox::KorgComboBox(juce::AudioParameterChoice* param)
    : meta::TimedParameterListener(param)
{
    if (param != nullptr)
    {
        auto choices = param->getAllValueStrings();
        for (int i = 0; i < choices.size(); i++)
            { addItem(choices[i], i + 1); }
        setSelectedId(param->getIndex() + 1, juce::dontSendNotification);
        param->addListener(this);
    }

    addListener(this);
}

void KorgComboBox::handleNewParameterValue()
{
    if (p_Parameter == nullptr) { return; }

    auto p_index = static_cast<juce::AudioParameterChoice*>(p_Parameter)->getIndex() + 1;
    auto s_index = getSelectedId();
    if (p_index != s_index)
        { setSelectedId(p_index); }
}

void KorgComboBox::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (p_Parameter != nullptr && p_Parameter->getCurrentValueAsText() != getText())
    {
        p_Parameter->beginChangeGesture();
        p_Parameter->setValueNotifyingHost(p_Parameter->getValueForText(getText()));
        p_Parameter->endChangeGesture();
    }
}
