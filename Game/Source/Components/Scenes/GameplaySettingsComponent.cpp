#include "GameplaySettingsComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Core/ServiceLocator.h>
#include <Engine/Misc/Enums.h>

#include <Components/Controllers/ControllerComponent.h>
#include <Components/CreatureSpawner.h>
#include <Components/LevelDisplayComponent.h>
#include <Components/Controllers/GeneralInputControllerComponent.h>
#include <Creatures/CreatureFactory.h>
#include <Events/EventArgLevel.h>
#include <Map/Block.h>
#include <Map/Graph.h>
#include <Misc/Constants.h>
#include <Misc/Enums.h>
#include <Misc/GlobalGameSettings.h>
#include <UserInterface/UIEngine.h>
#include <Misc/SerializedStructs.h>

#include <string>

void Game::GameplaySettingsComponent::SetupPlayers()
{
    auto player1InputMapping{ GameEngine::InputManager::Get().GetInputMapping("Player1") };
    auto player2InputMapping{ GameEngine::InputManager::Get().GetInputMapping("Player2") };

    GameEngine::GameObject& player1Obj{ m_pScene->CreateGameObject("Player1") };
    GameEngine::GameObject& player2Obj{ m_pScene->CreateGameObject("Player2") };

    CreatureFactory::BuildCreatureComponents(player1Obj, Creature::QBert, PlayerIndex::Player1);
    player1Obj.GetComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());

    switch (GlobalGameSettings::SelectedGamemode)
    {
        case Gamemode::Solo:
            player1Obj.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
        case Gamemode::Coop:
            player1Obj.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(2));

            CreatureFactory::BuildCreatureComponents(player2Obj, Creature::QBert, PlayerIndex::Player2);
            player2Obj.GetComponent<ControllerComponent>()->Init(player2InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
        case Gamemode::Versus:
            player1Obj.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(2));

            CreatureFactory::BuildCreatureComponents(player2Obj, Creature::Coily, PlayerIndex::Player2);
            player2Obj.GetComponent<ControllerComponent>()->Init(player2InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
    }
}

void Game::GameplaySettingsComponent::ResetPlayerPositions()
{
    auto pPlayer1Obj{ m_pScene->GetObjectByName("Player1") };
    auto pPlayer2Obj{ m_pScene->GetObjectByName("Player2") };


    switch (GlobalGameSettings::SelectedGamemode)
    {
    case Gamemode::Solo:
        if (pPlayer1Obj) pPlayer1Obj->GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(0, BlockSurface::Top));
        break;
    case Gamemode::Coop:
        if (pPlayer1Obj) pPlayer1Obj->GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(1, BlockSurface::Top));
        if (pPlayer1Obj) pPlayer2Obj->GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(2, BlockSurface::Top));
        break;
    case Gamemode::Versus:
        if (pPlayer1Obj) pPlayer1Obj->GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(0, BlockSurface::Top));
        if (pPlayer2Obj) pPlayer2Obj->GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(21, BlockSurface::Top));
        break;
    }
}

void Game::GameplaySettingsComponent::SetupRound(RoundInfo const& roundInfo)
{
    m_pScene->SendEventToAllObjects<GameEngine::EventArg>("OnRoundEnd");

    m_pEntityGraph->Init(roundInfo.StartingBlockColor, roundInfo.FinalBlockColor);

    Block::CycleBackColor = m_Gameplay_Info.LevelsInfo[m_CurrentLevel].CycleBackBlocks;
    Block::StartingBlockType = roundInfo.StartingBlockColor;
    Block::FinalBlockType = roundInfo.FinalBlockColor;

    ResetPlayerPositions();

    for (auto const& spawnerObject : m_SpawnerObjects)
    {
        //spawnerObject->GetComponent<CreatureSpawner>()->WipeSpawnedCreatures();
        spawnerObject->SetForDeletion();
    }

    m_SpawnerObjects.clear();

    for (auto const& creatureSpawnerInfo : roundInfo.CreatureSpawnersInfo)
    {
        auto& creatureSpawner{ m_pScene->CreateGameObject() };
        creatureSpawner.AddComponent<CreatureSpawner>()->Init(creatureSpawnerInfo);
        m_SpawnerObjects.push_back(&creatureSpawner);
    }
    
    GetOwner()->SendEvent<EventArgLevel>("OnNewRound", roundInfo.FinalBlockColor, m_CurrentLevel + 1, m_CurrentRound + 1);
}

void Game::GameplaySettingsComponent::OnSceneLoad()
{
    m_CurrentLevel = 0;
    m_CurrentRound = 0;
    m_PlayerDealthCounter = 0;
    GlobalGameSettings::PlayerScore = 0;

    SetupPlayers();
    SetupRound(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo[m_CurrentRound]);
}

void Game::GameplaySettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnRoundCompleted")
    {
        GoToNextRound();
    }
    else if (eventArg->EventId == "OnSkipRound")
    {
        GoToNextRound();
    }
    else if (eventArg->EventId == "OnPlayerDeath")
    {
        switch (GlobalGameSettings::SelectedGamemode)
        {
        case Gamemode::Coop:
        {
            ++m_PlayerDealthCounter;
            if (m_PlayerDealthCounter >= 2) GameEngine::SceneManager::Get().SetActiveScene("GameOver");
            break;
        }
        default:
            GameEngine::SceneManager::Get().SetActiveScene("GameOver");
        }
    }
    else if (eventArg->EventId == "OnSkipRound")
    {
        GoToNextRound();
    }
}

void Game::GameplaySettingsComponent::GoToNextRound()
{
    ++m_CurrentRound;

    if (m_CurrentRound < static_cast<int>(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo.size()))
    {
        SetupRound(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo[m_CurrentRound]);
        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(static_cast<int>(SoundEffect::Victory));
    }
    else
    {
        m_CurrentRound = 0;
        ++m_CurrentLevel;
        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(static_cast<int>(SoundEffect::LevelStart));

        if (m_CurrentLevel < static_cast<int>(m_Gameplay_Info.LevelsInfo.size()))
        {
            SetupRound(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo[m_CurrentRound]);
        }
        else
        {
            GameEngine::SceneManager::Get().SetActiveScene("GameWon");
        }
    }
}

void Game::GameplaySettingsComponent::Init(std::string const& jsonPath)
{
    json gameplayInfoJSON{ GameEngine::ResourceManager::Get().LoadJSON(jsonPath) };

    m_Gameplay_Info = gameplayInfoJSON.at(0).get<GameplayInfo>();
    UIEngine uiEngine{ m_Gameplay_Info.UIJSONPath };
    GetOwner()->AddComponent<LevelDisplayComponent>();

    SetupGraphs();
}

Game::GameplaySettingsComponent::GameplaySettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
}

void Game::GameplaySettingsComponent::SetupGraphs()
{
    auto& graphObj{ m_pScene->CreateGameObject("Graph") };
    graphObj.GetTransform()->SetLocalPosition(Screen::GAME_WIDTH / 2.f, 100.f);
    graphObj.GetTransform()->SetZIndex(-1);
    m_pEntityGraph = graphObj.AddComponent<Graph>();

    auto& discGraphObj{ m_pScene->CreateGameObject("DiscGraph") };
    discGraphObj.GetTransform()->SetLocalPosition(Screen::GAME_WIDTH / 2.f, 100.f - Block::BLOCK_SIZE);
    discGraphObj.GetTransform()->SetZIndex(-2);
    m_pDiscGraph = discGraphObj.AddComponent<Graph>();
    m_pDiscGraph->Init(BlockColor::Empty, BlockColor::Empty);
}
