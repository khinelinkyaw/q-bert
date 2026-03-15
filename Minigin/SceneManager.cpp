#include "Scene.h"
#include "SceneManager.h"

void Engine::SceneManager::FixedUpdate()
{
    for (auto& scene : m_scenes)
    {
        scene->FixedUpdate();
    }
}

void Engine::SceneManager::Update()
{
    for (auto& scene : m_scenes)
    {
        scene->Update();
    }
}

void Engine::SceneManager::Render()
{
    for (const auto& scene : m_scenes)
    {
        scene->Render();
    }
}

void Engine::SceneManager::CheckForDeletion()
{
    for (auto& scene : m_scenes)
    {
        scene->CheckForDeletion();
    }
}

Engine::Scene& Engine::SceneManager::CreateScene()
{
    m_scenes.emplace_back(new Scene());
    return *m_scenes.back();
}
