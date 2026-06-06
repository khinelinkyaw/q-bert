#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TransformComponent.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

namespace GameEngine
{
    class Texture2D;
    class GameObject final
    {
    private:
        static inline ObjectID NEXT_ID{ 0 };

        ObjectID m_Id{ NEXT_ID++ };
        bool m_MarkedForDeletion{ false };
        TransformComponent m_Transform{this};
        std::vector<std::unique_ptr<BaseComponent>> m_Components{};

    public:
        int GetId() const { return m_Id; }

        void FixedUpdate();
        void Update();
        void Render() const;

        TransformComponent* GetTransform() { return &m_Transform; }
        float GetZIndex() const { return m_Transform.GetZIndex(); }

        template<typename EventArgType, typename... Args> requires DerivedEventArg<EventArgType>
        void SendEvent(Args&& ... args);
        void SendEvent(std::unique_ptr<EventArg>&& pEventArg);

        template<typename ComponentType> requires DerivedComponent<ComponentType>
        ComponentType* AddComponent();
        void RemoveComponent(size_t index);
        template<typename ComponentType>
        ComponentType* GetComponent();

        void SetForDeletion();
        bool IsMarkedForDeletion() const;

        GameObject() = default;
        ~GameObject() = default;
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;
    };

    template<typename EventArgType, typename ...Args> requires DerivedEventArg<EventArgType>
    inline void GameObject::SendEvent(Args&& ...args)
    {
        std::unique_ptr<EventArg> pEventArg{ std::make_unique<EventArgType>(EventArgType{std::forward<Args>(args)...}) };
        SendEvent(std::move(pEventArg));
    }

    template<typename ComponentType> requires DerivedComponent<ComponentType>
    ComponentType* GameObject::AddComponent()
    {
        std::unique_ptr<ComponentType> newComponent{ std::make_unique<ComponentType>(this) };
        m_Components.push_back(std::move(newComponent));

        return static_cast<ComponentType*>(m_Components.back().get());
    }

    template<typename ComponentType>
    ComponentType* GameObject::GetComponent()
    {
        auto needed_component_type_id{ typeid(ComponentType).hash_code() };

        for (const auto& component : m_Components)
        {
            auto raw_ptr{ component.get() };

            if (needed_component_type_id == typeid(*raw_ptr).hash_code())
            {
                return static_cast<ComponentType*>(raw_ptr);
            }
        }

        return nullptr;
    }
}

#endif
