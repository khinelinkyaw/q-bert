#include "GameWonSettingsComponent.h"

#include <Components/Controllers/GeneralInputControllerComponent.h>

#include <Engine/Core/Time.h>
#include <Engine/Core/SceneManager.h>

void Game::GameWonSettingsComponent::Update()
{
    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime >= m_TransitionTime)
    {
        m_ElapsedTime = 0;
        GameEngine::SceneManager::Get().SetActiveScene("HighScore");
    }
}

Game::GameWonSettingsComponent::GameWonSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
}
