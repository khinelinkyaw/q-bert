#include "GameObject.h"
#include "Transform.h"

void Engine::GameObject::SetForDeletion()
{
    m_MarkedForDeletion = true;
}

bool Engine::GameObject::IsMarkedForDeletion() const
{
    return m_MarkedForDeletion;
}

void Engine::GameObject::FixedUpdate()
{
    for (auto& component : m_Components)
    {
        component->FixedUpdate();
    }
}

void Engine::GameObject::Update()
{
    for (auto& component : m_Components)
    {
        component->Update();
    }
}

void Engine::GameObject::Render() const
{
    const auto& pos = m_Transform.GetPosition();

    for (const auto& component : m_Components)
    {
        component->Render(pos);
    }
}

void Engine::GameObject::SetPosition(float x, float y)
{
    m_Transform.SetPosition(x, y, 0.0f);
}

void Engine::GameObject::SetPosition(Transform newPosition)
{
    m_Transform = newPosition;
}

void Engine::GameObject::RemoveComponent(size_t index)
{
    if (index < m_Components.size())
    {
        m_Components.erase(m_Components.begin() + index);
    }
}
