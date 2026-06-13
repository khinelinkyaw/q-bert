#include <Engine/Core/Macros.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Misc/Types.h>
#include <Engine/Core/GameObject.h>

#include <memory>
#include <string>
#include <utility>

using namespace GameEngine;

void SceneManager::FixedUpdate()
{
    m_Scenes[m_ActiveSceneName]->FixedUpdate();
}

void SceneManager::Update()
{
    m_Scenes[m_ActiveSceneName]->Update();
}

void SceneManager::Render()
{
    m_Scenes[m_ActiveSceneName]->Render();
}

void SceneManager::CheckForDeletion()
{
    m_Scenes[m_ActiveSceneName]->CheckForDeletion();
}

void GameEngine::SceneManager::CheckForSceneChange()
{
    if (m_PendingSceneChange)
    {
        m_ActiveSceneName = m_PendingActiveSceneName;
        m_PendingSceneChange = false;
        m_Scenes[m_ActiveSceneName]->Load();
    }
}

Scene& SceneManager::CreateScene(std::string const& name)
{
    if (m_Scenes.find(name) != m_Scenes.end())
    {
        DEBUG_CONSOLE("SceneManager","Scene with name " + name + " already exists. Returning existing scene.")
        return *m_Scenes[name];
    }

    if (m_Scenes.empty())
    {
        m_ActiveSceneName = name;
    }

    m_Scenes[name] = std::unique_ptr<Scene>(new Scene());
    return *m_Scenes[name];
}

Scene* GameEngine::SceneManager::GetScene(std::string const& name) const
{
    if (auto sceneIter{ m_Scenes.find(name) }; sceneIter != m_Scenes.end())
    {
        return sceneIter->second.get();
    }

    return nullptr;
}

Scene* GameEngine::SceneManager::GetActiveScene() const
{
    return GetScene(m_ActiveSceneName);
}

bool GameEngine::SceneManager::SetActiveScene(std::string const& name)
{
    if (m_Scenes.find(name) != m_Scenes.end())
    {
        m_PendingSceneChange = true;
        m_PendingActiveSceneName = name;
        return true;
    }

    return false;
}

bool GameEngine::SceneManager::SetActiveScene(Scene* scene)
{
    for (auto const& [name, scenePtr] : m_Scenes)
    {
        if (scenePtr.get() == scene)
        {
            return SetActiveScene(name);
        }
    }

    return false;
}
