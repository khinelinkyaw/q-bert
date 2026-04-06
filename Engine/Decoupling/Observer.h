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

    class NullObserver final : public Observer
    {
    public:
        void OnNotify(GameObject const&, std::string) override {};
        ~NullObserver() override = default;
    };
}

#endif