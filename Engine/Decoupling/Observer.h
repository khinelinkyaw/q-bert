#ifndef OBSERVER_H
#define OBSERVER_H

#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>

namespace GameEngine
{
    class TextComponent;
    class GameObject;

    template<typename...ArgTypes>
    class Observer
    {
    private:
        std::unordered_map<std::string, void(*)(ArgTypes...)> m_EventBindings;

    public:
        void OnNotify(std::string eventId, ArgTypes&& ...args);
        void BindEvent(std::string eventId, void(*func)(ArgTypes...));

        Observer();
        virtual ~Observer() = default;
    };

    template<typename ...ArgTypes> 
    inline void Observer<ArgTypes...>::OnNotify(std::string eventId, ArgTypes && ...args)
    {
        assert(m_EventBindings.contains(eventId));

        auto event{ m_EventBindings[eventId] };
        event(std::forward<ArgTypes>(args)...);
    }

    template<typename ...ArgTypes>
    inline void Observer<ArgTypes...>::BindEvent(std::string eventId, void(*func)(ArgTypes...))
    {
        m_EventBindings.insert({ eventId, func });
    }

    template<typename ...ArgTypes>
    inline Observer<ArgTypes...>::Observer()
        : m_EventBindings{}
    {
    }
}

#endif