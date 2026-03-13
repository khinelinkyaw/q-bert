#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <unordered_map>

namespace dae
{
    template<typename T> concept DerivedMessageClass = std::is_base_of<Message, T>::value;

    class Sender;
    class Receiver;

    class Message
    {
    private:
        size_t m_Hash;

    public:
        Message(size_t hash) : m_Hash{ hash } {};
        virtual ~Message() = default;
    };

    class MessageQueue final
    {
    private:
        constexpr static uint8_t m_QueueSize{ 255 };
        std::vector<Sender*> m_Senders{};
        std::unordered_map<std::string,Receiver*> m_Receivers{};
        std::hash<std::string> m_HashFunction{};
        std::array<std::unique_ptr<Message>, m_QueueSize> m_MessageQueue{};

        size_t m_QueueHead{};
        size_t m_QueueTail{};
    public:
        ~MessageQueue() = default;

        template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
        void OnMessage(Args&& ... args);

    };

    template<typename MessageType, typename... Args> requires DerivedMessageClass<MessageType>
    inline void MessageQueue::OnMessage(Args && ...args)
    {
        m_MessageQueue[m_QueueTail] = std::make_unique<MessageType>(std::forward<Args>(args...));
        m_QueueTail = (m_QueueTail + 1) % m_QueueSize;
    }
}


#endif