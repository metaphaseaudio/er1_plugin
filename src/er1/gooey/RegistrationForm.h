//
// Created by Matt on 11/28/2024.
//

#pragma once
#include <juce_product_unlocking/juce_product_unlocking.h>


class RegistrationForm
    : public juce::OnlineUnlockForm
{
public:
    explicit RegistrationForm(juce::OnlineUnlockStatus& status);

    void dismiss() override { setVisible(false); }
};
