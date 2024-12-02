//
// Created by Matt on 11/28/2024.
//

#include "Authentication.h"

#include <memory>
static const juce::RSAKey PUB(
    "5,815bdb0a12eafbf9de78b12ec15127255bceec32cf60e36d5eae02ca1e74f4297101a3c4b1df2330bf65bf45f242fdb47b12f0c37fc17a2a86033c73354e5aa95ba7463bedde8d55d5a7b39719c8a006907ffcf30588f072b8b4d184f1463f8c266b4342886e16f967f5b259ccc7b2b95845009cb9b1fe23de41e7725fcc46c56e1123be93263545cda1de5d26c36c84ee29053e1394190f9a88892fb90d4fe80d65aeab82490ae59b2de7d71c44c28397e3ebcb349ccc0d812c4406b6df314030b40c778b4f8f24e6ed6506206dd33d7c41d275521ed0cff692f5c36ef6bbd4f64e053c217575f294729df79c3b8b60ae32f47b50768dcaae2cdb20f0eaa5d5"
);

static const juce::RSAKey PRI(
    "19df2bced09565985fb1bd0959dd07d4458fc8d6f64693e2ac8933c20617640849cd20c0f05fd3d68cadf30dfd409924189d635a4cc04ba21acd727d710fabbb78bb0e0bfc5fb5ddf787f0b7d1f4ecce1ce665ca344e967d582429e76374731c07af0d73b4e2d16514cabd4528f4bd5844da99b8f1f066072c7394b0798f415a66c69b9f02f2b8e3c247173b8a6836c96186472c2a5024ae0230cdf462c5f5d4f9226ef91d1d83820ea51afdd4c41ce7312743e0704fa87899a5f33f3adb0c4dc3d2d667d085c89e40407c5af103543a1ea719f343b550b45af5e108f3df8c5d18709dc5cb53b10729049b5ecf5d5024b3f523c74049fa3bfefe87aee900956d,815bdb0a12eafbf9de78b12ec15127255bceec32cf60e36d5eae02ca1e74f4297101a3c4b1df2330bf65bf45f242fdb47b12f0c37fc17a2a86033c73354e5aa95ba7463bedde8d55d5a7b39719c8a006907ffcf30588f072b8b4d184f1463f8c266b4342886e16f967f5b259ccc7b2b95845009cb9b1fe23de41e7725fcc46c56e1123be93263545cda1de5d26c36c84ee29053e1394190f9a88892fb90d4fe80d65aeab82490ae59b2de7d71c44c28397e3ebcb349ccc0d812c4406b6df314030b40c778b4f8f24e6ed6506206dd33d7c41d275521ed0cff692f5c36ef6bbd4f64e053c217575f294729df79c3b8b60ae32f47b50768dcaae2cdb20f0eaa5d5"
);

static const juce::RSAKey PUBLICK_KEY("10001,"
                                      "90f582e37b5598e57967a055a91361777cfd95f85e6e1ceaba665150f3f21bc949be85e4a5a9689a7e0d6956b1730490c730a88be7338a26b5cec2105730ab6101f3387d751d368c66fbfee13459b2e0f28fb960555cbde11d44b348ad0ffa9384fd0e867568ca7834c3a1a32d924d2cfdfbc4f0a6e46f75eac5822265ffd069dae868f32a21525a4d9391cec73d29315055f3ae4162fcde82eddc8633d929d039c3d1d6e64dfb1aaa68b8e3a2a990db647522e29464cfc688ad78c9c085f92ba58fb9deb3e17782120e6370651408a0207108c26517567b0e308a1dd7b4378967f7567bc633976be493ff67b240b7715c9d6dbac51125c88db645dc04ddd9c036ff194e7f44b2f087");


juce::String Authentication::getProductID()
{
    return "MP-1";
}

bool Authentication::doesProductIDMatch(const juce::String& returnedIDFromServer)
{
    return returnedIDFromServer == getProductID();
}

juce::RSAKey Authentication::getPublicKey()
{
    return PUB;
}

juce::String Authentication::getWebsiteName()
{
    return "localhost:5000";
}

juce::URL Authentication::getServerAuthenticationURL()
{
    return {"http://localhost:5000/metaphase/auth"};
}

juce::String Authentication::readReplyFromWebserver(const juce::String& email, const juce::String& password)
{
    juce::URL url(getServerAuthenticationURL()
                     .withParameter("product", getProductID())
                     .withParameter("email", email)
                     .withParameter("pw", password)
                     .withParameter("os", juce::SystemStats::getOperatingSystemName())
                     .withParameter("mach", getLocalMachineIDs()[0]));

    DBG ("Trying to unlock via URL: " << url.toString (true));

    {
        std::lock_guard lock(m_StreamCreationLock);
        m_Stream = std::make_unique<juce::WebInputStream>(url, true);
    }

    if (m_Stream->connect(nullptr))
    {
        auto thread = juce::Thread::getCurrentThread();
        juce::MemoryOutputStream result;

        while(!(m_Stream->isExhausted() || m_Stream->isError() || (thread != nullptr && thread->threadShouldExit())))
        {
            auto bytesRead = result.writeFromInputStream (*m_Stream, 8192);

            if (bytesRead < 0)
                break;
        }

        return result.toString();
    }

    return {};
}

void Authentication::saveState(const juce::String& string)
{
    std::cout << string << std::endl;
}

juce::String Authentication::getState()
{
    return juce::String();
}

void Authentication::userCancelled()
{
    std::lock_guard lock(m_StreamCreationLock);

    if (m_Stream != nullptr)
        m_Stream->cancel();
}
