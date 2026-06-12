#include "MainMenuSettingsComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Enums.h>

#include <Misc/Enums.h>
#include <Misc/GlobalGameSettings.h>
#include <Components/Scenes/GameplaySettingsComponent.h>

void Game::MainMenuSettingsComponent::UpdateSelectorPosition()
{
    auto gamemodeNameObj{ m_GamemodeNames.at(m_SelectedGamemode) };

    m_pSelector->GetTransform()->SetLocalY(gamemodeNameObj->GetTransform()->GetLocalPosition().y);
}

void Game::MainMenuSettingsComponent::MoveSelector(GameEngine::Direction direction)
{
    int nextGamemode{};

    switch (direction)
    {
    case GameEngine::Direction::Up:
    {
        nextGamemode = static_cast<int>(m_SelectedGamemode) - 1;
        break;
    }
    case GameEngine::Direction::Down:
    {
        nextGamemode = static_cast<int>(m_SelectedGamemode) + 1;
        break;
    }
    default:
        break;
    }

    if (nextGamemode <= static_cast<int>(Gamemode::Versus) and nextGamemode >= static_cast<int>(Gamemode::Solo))
    {
        m_SelectedGamemode = static_cast<Gamemode>(nextGamemode);
        UpdateSelectorPosition();
    }
}

void Game::MainMenuSettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnSelectorUp")
    {
        MoveSelector(GameEngine::Direction::Up);
    }
    else if (eventArg->EventId == "OnSelectorDown")
    {
        MoveSelector(GameEngine::Direction::Down);
    }
     else if (eventArg->EventId == "OnSelectorConfirm")
     {
        GlobalGameSettings::SelectedGamemode = m_SelectedGamemode;
        auto gameplayScene{ GameEngine::SceneManager::Get().GetScene("Gameplay")};
        GameEngine::SceneManager::Get().SetActiveScene(gameplayScene);
        auto gameplaySettingsObj{ gameplayScene->GetObjectByName("GameplaySettings") };
        gameplaySettingsObj->GetComponent<GameplaySettingsComponent>()->Init("JSON/Levels.json");
     }
}

Game::MainMenuSettingsComponent::MainMenuSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
{
}
