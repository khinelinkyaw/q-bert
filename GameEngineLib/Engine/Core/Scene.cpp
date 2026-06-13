#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Misc/Types.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iterator>

using namespace GameEngine;

void Scene::Add(std::unique_ptr<GameObject> object)
{
    assert(object != nullptr && "Cannot add a null GameObject to the scene.");
    m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
    m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
        [&object](const auto& ptr)
        {
            return ptr.get() == &object;
        }),
        m_Objects.end());
}

void Scene::RemoveAll() { m_Objects.clear(); }

void GameEngine::Scene::Load()
{
    for (int index{ 0 }; index < static_cast<int>(m_Objects.size()); ++index)
    {
        m_Objects[index]->Load();
    }
}

void Scene::FixedUpdate()
{
    for (int index{ 0 }; index < static_cast<int>(m_Objects.size()); ++index)
    {
        m_Objects[index]->FixedUpdate();
    }

    ServiceLocator::Get().GetCollisionSystem().CheckCollisions();
}

void Scene::Update()
{
    for (int index{ 0 }; index < static_cast<int>(m_Objects.size()); ++index)
    {
        m_Objects[index]->Update();
    }
}

void Scene::Render() const
{   
    SortObjectsForRendering();

    for (const auto& object : m_SortedRenderObjects)
    {
        object->Render();
    }
}

void Scene::CheckForDeletion()
{
    std::vector<std::unique_ptr<GameObject>> remaining_objects;
    remaining_objects.reserve(m_Objects.size());

    for (auto& object : m_Objects)
    {
        if (!object->IsMarkedForDeletion())
        {
            remaining_objects.push_back(std::move(object));
        }
        else
        {
            UnsetGameObjectName(object->GetId());
        }
    }

    m_Objects = std::move(remaining_objects);
}

GameObject* GameEngine::Scene::GetObjectById(ObjectID id) const
{
    for (auto const& object : m_Objects)
    {
        if (object->GetId() == id)
        {
            return object.get();
        }
    }

    return nullptr;
}

GameObject* GameEngine::Scene::GetObjectByName(std::string const& name) const
{
    if (auto iter{ m_NameToIdMap.find(name) }; iter != m_NameToIdMap.end())
    {
        return GetObjectById(iter->second);
    }
    return nullptr;
}

bool GameEngine::Scene::SetObjectName(std::string const& name, ObjectID id)
{
    auto obj{ GetObjectById(id) };

    if (obj == nullptr) return false;

    m_NameToIdMap[name] = id;
    return true;
}

void GameEngine::Scene::SortObjectsForRendering() const
{
    m_SortedRenderObjects.clear();
    m_SortedRenderObjects.reserve(m_Objects.size());

    std::transform(m_Objects.begin(), m_Objects.end(), std::back_inserter(m_SortedRenderObjects),
        [](auto const& objectPtr)
        {
            return objectPtr.get();
        });

    std::ranges::sort(m_SortedRenderObjects, std::ranges::less{}, [](GameObject const* pGameObject)
        {
            return pGameObject->GetZIndex();
        });
}

GameObject& GameEngine::Scene::CreateGameObject()
{
    m_Objects.push_back(std::make_unique<GameObject>());
    return *m_Objects.back().get();
}

GameObject& GameEngine::Scene::CreateGameObject(std::string const& name)
{
    m_Objects.push_back(std::make_unique<GameObject>());
    auto createdObject{ m_Objects.back().get() };
    SetObjectName(name, createdObject->GetId());
    return *createdObject;
}

bool GameEngine::Scene::UnsetGameObjectName(ObjectID id)
{
    auto iter{ std::ranges::find_if(m_NameToIdMap, [id](const auto& pair)
    {
        return pair.second == id;
    }) };

    if (iter != m_NameToIdMap.end())
    {
        m_NameToIdMap.erase(iter);
        return true;
    }
    return false;
}
