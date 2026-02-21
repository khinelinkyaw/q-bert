#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace dae
{
    class Texture2D;
    class GameObject final
    {
        bool m_MarkedForDeletion{ false };
        Transform m_transform{};
        std::shared_ptr<Texture2D> m_texture{};
        std::vector<std::unique_ptr<BaseComponent>> m_Components{};

    public:
        virtual void FixedUpdate();
        virtual void Update(float deltaTime);
        virtual void Render() const;

        void SetTexture(const std::string& filename);
        void SetPosition(float x, float y);

        template<typename ComponentType, typename... Args>
        size_t AddComponent(Args&&... args);
        void RemoveComponent(size_t index);
        template<typename ComponentType>
        ComponentType& GetComponent(size_t index);

        void SetForDeletion();
        bool IsMarkedForDeletion() const;

        GameObject() = default;
        virtual ~GameObject();
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;
    };

    template<typename ComponentType, typename... Args>
    size_t GameObject::AddComponent(Args&&... args)
    {
        m_Components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(args)...));
        return m_Components.size() - 1;
    }

    template<typename ComponentType>
    ComponentType& GameObject::GetComponent(size_t index)
    {
        if (index < m_Components.size())
        {
            return static_cast<ComponentType&>(*m_Components[index]);
        }
        throw std::out_of_range("Component index out of range");
    }
}

