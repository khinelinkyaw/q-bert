#include <string>
#ifndef OBSERVER_H
#define OBSERVER_H

namespace GameEngine
{
    class GameObject;
    class Observer
    {
    public:
        virtual void OnNotify(GameObject const& gameObject, std::string eventId) = 0;
        virtual ~Observer() = default;
    };
}

#endif