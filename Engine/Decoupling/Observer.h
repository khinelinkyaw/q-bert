#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <unordered_map>

namespace GameEngine
{
    class TextComponent;
    class GameObject;

    class Observer
    {
    private:
        std::unordered_map<std::string, void(*)(GameObject&)> m_EventBindings;

    public:
        void OnNotify(GameObject& gameObject, std::string eventId);
        void BindEvent(std::string eventId, void(*func)(GameObject&));

        Observer();
        virtual ~Observer() = default;
    };

    //class NullObserver final : public Observer
    //{
    //public:
    //    void OnNotify(GameObject const&, std::string) override {};
    //    ~NullObserver() override = default;
    //};

    //class TextObserver : public Observer
    //{
    //private:
    //    TextComponent* m_pTextComponent;
    //public:
    //    ~TextObserver() override = default;
    //};
}

#endif