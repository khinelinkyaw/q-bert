#pragma once
#include "Components/BaseComponent.h"
#include "Transform.h"
#include <memory>
#include <utility>
#include <vector>

namespace dae
{
    class Texture2D;
    class GameObject final
    {
        bool m_MarkedForDeletion{ false };
        Transform m_transform{};
        std::vector<std::unique_ptr<BaseComponent>> m_Components{};

    public:
        void FixedUpdate();
        void Update(float deltaTime);
        void Render() const;

        void SetPosition(float x, float y);

        template<typename ComponentType, typename... Args>
        void AddComponent(Args&&... args);
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

    template<typename ComponentType, typename... Args>
    void GameObject::AddComponent(Args&&... args)
    {
        m_Components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(args)...));
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

