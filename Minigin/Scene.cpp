#include "GameObject.h"
#include "Scene.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

using namespace dae;

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

void Scene::FixedUpdate()
{
    for (auto& object : m_Objects)
    {
        object->FixedUpdate();
    }
}

void dae::Scene::Update(float deltaTime)
{
    for (auto& object : m_Objects)
    {
        object->Update(deltaTime);
    }
}

void Scene::Render() const
{
    for (const auto& object : m_Objects)
    {
        object->Render();
    }
}

void dae::Scene::CheckForDeletion()
{
    std::vector<std::unique_ptr<GameObject>> remaining_objects;
    remaining_objects.reserve(m_Objects.size());

    for (auto& object : m_Objects)
    {
        if (!object->IsMarkedForDeletion())
        {
            remaining_objects.push_back(std::move(object));
        }
    }

    m_Objects = std::move(remaining_objects);
}
