#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>

#include <memory>
#include <vector>

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
//
//void GameEngine::GameObject::SendEvent(std::unique_ptr<EventArg>&& pEventArg)
//{
//    if (pEventArg->EventId == "OnCollisionEnter")
//    {
//        for (const auto& component : m_Components)
//        {
//            auto otherObject = static_cast<EventArgCollision*>(pEventArg.get())->OtherObject;
//            component->OnCollisionEnter(otherObject);
//        }
//        return;
//    }
//    else if (pEventArg->EventId == "OnCollisionStay")
//    {
//        for (const auto& component : m_Components)
//        {
//            auto otherObject = static_cast<EventArgCollision*>(pEventArg.get())->OtherObject;
//            component->OnCollisionStay(otherObject);
//        }
//        return;
//    }
//    else if (pEventArg->EventId == "OnCollisionExit")
//    {
//        for (const auto& component : m_Components)
//        {
//            auto otherObject = static_cast<EventArgCollision*>(pEventArg.get())->OtherObject;
//            component->OnCollisionExit(otherObject);
//        }
//        return;
//    }
//
//    for (const auto& component : m_Components)
//    {
//        component->OnEvent(pEventArg.get());
//    }
//}

void GameObject::RemoveComponent(size_t index)
{
    if (index < m_Components.size())
    {
        m_Components.erase(m_Components.begin() + index);
    }
}
