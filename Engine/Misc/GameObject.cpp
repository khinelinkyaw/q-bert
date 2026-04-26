#include "GameObject.h"

using namespace GameEngine;

void GameObject::SetForDeletion()
{
    m_MarkedForDeletion = true;
}

bool GameObject::IsMarkedForDeletion() const
{
    return m_MarkedForDeletion;
}

void GameObject::FixedUpdate()
{
    for (auto& component : m_Components)
    {
        component->FixedUpdate();
    }
}

void GameObject::Update()
{
    for (auto& component : m_Components)
    {
        component->Update();
    }
}

void GameObject::Render() const
{
    const auto& pos = m_Transform.GetWorldPosition();

    for (const auto& component : m_Components)
    {
        component->Render(pos);
    }
}

void GameObject::SetPosition(float x, float y)
{
    m_Transform.SetLocalPosition(glm::vec3{ x, y, 0.f });
}

void GameObject::SetPosition(glm::vec3 newPos)
{
    m_Transform.SetLocalPosition(newPos);
}

void GameObject::RemoveComponent(size_t index)
{
    if (index < m_Components.size())
    {
        m_Components.erase(m_Components.begin() + index);
    }
}
