#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <Engine/Utils/MiniMessage.h>

namespace GameEngine
{
    typedef std::uint64_t hash_t;

    //template<typename T> concept DerivedMessageClass = std::is_base_of<Message, T>::value;
    
    class Receiver;
    class MessageQueue final
    {
    private:
        constexpr static int m_QueueSize{ 255 };
        int m_QueueHead{};
        int m_QueueTail{};

        std::unordered_map<hash_t,Receiver*> m_Receivers{};
        std::array<std::unique_ptr<MiniMessage>, m_QueueSize> m_MessageQueue{};

    public:
        ~MessageQueue() = default;

        //template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
        //void OnMessage(Args&& ... args);

        void SendMessage(std::string const& messageID);
        void RouteMessage();

        MessageQueue() = default;
    };

    //template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
    //inline void MessageQueue::OnMessage(Args && ...args)
    //{
    //    m_MessageQueue[m_QueueTail] = std::make_unique<MessageType>(std::forward<Args>(args)...);
    //    m_QueueTail = (m_QueueTail + 1) % m_QueueSize;
    //}
}

#endif
