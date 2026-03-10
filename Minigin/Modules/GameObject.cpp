#include "GameObject.h"
#include "Transform.h"

void dae::GameObject::SetForDeletion()
{
    m_MarkedForDeletion = true;
}

bool dae::GameObject::IsMarkedForDeletion() const
{
    return m_MarkedForDeletion;
}

void dae::GameObject::FixedUpdate()
{
    for (auto& component : m_Components)
    {
        component->FixedUpdate();
    }
}

void dae::GameObject::Update()
{
    for (auto& component : m_Components)
    {
        component->Update();
    }
}

void dae::GameObject::Render() const
{
    const auto& pos = m_Transform.GetPosition();

    for (const auto& component : m_Components)
    {
        component->Render(pos);
    }
}

void dae::GameObject::SetPosition(float x, float y)
{
    m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetPosition(Transform newPosition)
{
    m_Transform = newPosition;
}

void dae::GameObject::RemoveComponent(size_t index)
{
    if (index < m_Components.size())
    {
        m_Components.erase(m_Components.begin() + index);
    }
}
