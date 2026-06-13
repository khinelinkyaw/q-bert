#include "GameWonSettingsComponent.h"

#include <Components/Controllers/GeneralInputControllerComponent.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Core/Time.h>

void Game::GameWonSettingsComponent::Update()
{
    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime >= m_TransitionTime)
    {
        m_ElapsedTime = 0;
        GameEngine::SceneManager::Get().SetActiveScene("NameInput");
    }
}

Game::GameWonSettingsComponent::GameWonSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
}
