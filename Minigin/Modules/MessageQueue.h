#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "CompileTimeHashing.h"
#include <array>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Engine
{
    class Message final
    {
    private:
        hash_t m_EventID;
    public:
        hash_t GetID() const { return m_EventID; }

        Message() = default;
        Message(std::string const& str);
        ~Message() = default;
    };

    class Receiver
    {
    public:
        virtual void HandleMessage(std::unique_ptr<Message> message) = 0;
        virtual ~Receiver() = default;
    };

    template<typename T> concept DerivedMessageClass = std::is_base_of<Message, T>::value;
    
    class MessageQueue final
    {
    private:
        constexpr static int m_QueueSize{ 255 };
        int m_QueueHead{};
        int m_QueueTail{};

        std::unordered_map<hash_t,Receiver*> m_Receivers{};
        std::array<std::unique_ptr<Message>, m_QueueSize> m_MessageQueue{};

    public:
        ~MessageQueue() = default;

        template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
        void OnMessage(Args&& ... args);
        void RouteMessage();
    };

    template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
    inline void MessageQueue::OnMessage(Args && ...args)
    {
        m_MessageQueue[m_QueueTail] = std::make_unique<MessageType>(std::forward<Args>(args)...);
        m_QueueTail = (m_QueueTail + 1) % m_QueueSize;
    }
}


#endif
