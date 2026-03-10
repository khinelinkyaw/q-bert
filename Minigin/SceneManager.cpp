#include "Scene.h"
#include "SceneManager.h"

void dae::SceneManager::FixedUpdate()
{
    for (auto& scene : m_scenes)
    {
        scene->FixedUpdate();
    }
}

void dae::SceneManager::Update()
{
    for (auto& scene : m_scenes)
    {
        scene->Update();
    }
}

void dae::SceneManager::Render()
{
    for (const auto& scene : m_scenes)
    {
        scene->Render();
    }
}

void dae::SceneManager::CheckForDeletion()
{
    for (auto& scene : m_scenes)
    {
        scene->CheckForDeletion();
    }
}

dae::Scene& dae::SceneManager::CreateScene()
{
    m_scenes.emplace_back(new Scene());
    return *m_scenes.back();
}
