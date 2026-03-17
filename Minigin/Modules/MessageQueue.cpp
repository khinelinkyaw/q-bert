#include "CompileTimeHashing.h"
#include "MessageQueue.h"
#include <string>
#include <utility>

using namespace Engine;

Message::Message(std::string const& str)
    : m_EventID{ hash_compile_time(str.c_str()) }
{
}

void MessageQueue::RouteMessage()
{
    if (m_QueueHead == m_QueueTail) return;

    auto l_MessageID{ m_MessageQueue[m_QueueHead]->GetID() };

    if (m_Receivers.count(l_MessageID) == 0) return;

    auto l_Receiver{ m_Receivers[l_MessageID] };

    l_Receiver->HandleMessage(std::move(m_MessageQueue[m_QueueHead]));

    m_QueueHead = (m_QueueHead + 1) % m_QueueSize;
}
