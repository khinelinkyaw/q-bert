#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <type_traits>

namespace GameEngine
{
    struct EventArg
    {
        std::string EventId{};
    };

    template<typename T> concept DerivedEventArg = std::is_base_of<EventArg, T>::value;
}

#endif