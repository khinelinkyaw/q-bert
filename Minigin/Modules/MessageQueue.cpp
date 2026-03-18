#include "MessageQueue.h"
#include <memory>
#include <string>
#include <utility>

constexpr GameEngine::Message::Message(std::string const& str)
    : m_MessageID{ HashCompileTime(str.c_str()) }
{
}

void GameEngine::MessageQueue::SendMessage(std::string const& messageID)
{
    m_MessageQueue[m_QueueTail] = std::make_unique<Message>(messageID);
    m_QueueTail = (m_QueueTail + 1) % m_QueueSize;
}

void GameEngine::MessageQueue::RouteMessage()
{
    if (m_QueueHead == m_QueueTail) return;

    auto l_MessageID{ m_MessageQueue[m_QueueHead]->GetID() };

    if (m_Receivers.count(l_MessageID) == 0)
    {
        m_QueueHead = (m_QueueHead + 1) % m_QueueSize;
        return;
    }

    auto l_Receiver{ m_Receivers[l_MessageID] };

    l_Receiver->HandleMessage(std::move(m_MessageQueue[m_QueueHead]));

    m_QueueHead = (m_QueueHead + 1) % m_QueueSize;
}
