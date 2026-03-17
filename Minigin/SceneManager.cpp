#include "Scene.h"
#include "SceneManager.h"

using namespace Engine;

void SceneManager::FixedUpdate()
{
    for (auto& scene : m_scenes)
    {
        scene->FixedUpdate();
    }
}

void SceneManager::Update()
{
    for (auto& scene : m_scenes)
    {
        scene->Update();
    }
}

void SceneManager::Render()
{
    for (const auto& scene : m_scenes)
    {
        scene->Render();
    }
}

void SceneManager::CheckForDeletion()
{
    for (auto& scene : m_scenes)
    {
        scene->CheckForDeletion();
    }
}

Scene& SceneManager::CreateScene()
{
    m_scenes.emplace_back(new Scene());
    return *m_scenes.back();
}
