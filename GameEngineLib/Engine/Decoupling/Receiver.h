#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>

namespace GameEngine
{
    class MiniMessage;
    class Receiver
    {
    public:
        virtual void HandleMessage(std::unique_ptr<MiniMessage> message) = 0;
        virtual ~Receiver() = default;
    };
}

#endif
