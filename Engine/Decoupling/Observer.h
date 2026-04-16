#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

namespace GameEngine
{
    class TextComponent;
    class GameObject;

    class Observer
    {
    public:
        virtual void OnNotify(GameObject& gameObject, std::string eventId) = 0;
        virtual ~Observer() = default;
    };

    class NullObserver final : public Observer
    {
    public:
        void OnNotify(GameObject&, std::string) override {};

        NullObserver();
        ~NullObserver() override = default;
    };
}

#endif