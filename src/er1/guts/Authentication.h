//
// Created by Matt on 11/28/2024.
//

#pragma once
#include <juce_product_unlocking/juce_product_unlocking.h>


class Authentication
    : public juce::OnlineUnlockStatus
{
public:
    juce::String getProductID() override;

    bool doesProductIDMatch(const juce::String& returnedIDFromServer) override;

    juce::RSAKey getPublicKey() override;

    void saveState(const juce::String& string) override;

    juce::String getState() override;

    juce::String getWebsiteName() override;

    void userCancelled() override;

    juce::URL getServerAuthenticationURL() override;

    juce::String readReplyFromWebserver(const juce::String& email, const juce::String& password) override;

private:
    std::mutex m_StreamCreationLock;
    std::unique_ptr<juce::WebInputStream> m_Stream;
};
