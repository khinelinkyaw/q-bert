#include "GameplaySettingsComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Misc/Enums.h>

#include <Components/Controllers/ControllerComponent.h>
#include <Components/CreatureSpawner.h>
#include <Components/LevelDisplayComponent.h>
#include <Creatures/CreatureFactory.h>
#include <Events/EventArgLevel.h>
#include <Map/Block.h>
#include <Map/Graph.h>
#include <Misc/Constants.h>
#include <Misc/Enums.h>
#include <Misc/GlobalGameSettings.h>
#include <UserInterface/UIEngine.h>
#include <Misc/SerializedStructs.h>

#include <memory>
#include <string>
#include <utility>

void Game::GameplaySettingsComponent::SetupPlayers()
{
    auto player1InputMapping{ GameEngine::InputManager::Get().GetInputMapping("Player1") };
    auto player2InputMapping{ GameEngine::InputManager::Get().GetInputMapping("Player2") };

    CreatureFactory::BuildCreatureComponents(m_pPlayer1, Creature::QBert, PlayerIndex::Player1);
    m_pPlayer1.GetComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetKeyboardInputDevice());

    switch (GlobalGameSettings::SelectedGamemode)
    {
        case Gamemode::Solo:
            m_pPlayer1.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
        case Gamemode::Coop:
            m_pPlayer1.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(2));

            CreatureFactory::BuildCreatureComponents(m_pPlayer2, Creature::QBert, PlayerIndex::Player2);
            m_pPlayer2.GetComponent<ControllerComponent>()->Init(player2InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
        case Gamemode::Versus:
            m_pPlayer1.AddComponent<ControllerComponent>()->Init(player1InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(2));

            CreatureFactory::BuildCreatureComponents(m_pPlayer2, Creature::Coily, PlayerIndex::Player2);
            m_pPlayer2.GetComponent<ControllerComponent>()->Init(player2InputMapping, &GameEngine::InputManager::Get().GetGamepadInputDevice(1));
            break;
    }
}

void Game::GameplaySettingsComponent::ResetPlayerPositions()
{
    switch (GlobalGameSettings::SelectedGamemode)
    {
    case Gamemode::Solo:
        m_pPlayer1.GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(0, BlockSurface::Top));
        break;
    case Gamemode::Coop:
        m_pPlayer1.GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(1, BlockSurface::Top));
        m_pPlayer2.GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(2, BlockSurface::Top));
        break;
    case Gamemode::Versus:
        m_pPlayer1.GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(0, BlockSurface::Top));
        m_pPlayer2.GetTransform()->SetLocalPosition(m_pEntityGraph->GetBlockSurfaceCenter(21, BlockSurface::Top));
        break;
    }
}

void Game::GameplaySettingsComponent::SetupRound(RoundInfo const& roundInfo)
{
    m_pEntityGraph->Init(roundInfo.StartingBlockColor, roundInfo.FinalBlockColor);

    Block::CycleBackColor = m_Gameplay_Info.LevelsInfo[m_CurrentLevel].CycleBackBlocks;
    Block::StartingBlockType = roundInfo.StartingBlockColor;
    Block::FinalBlockType = roundInfo.FinalBlockColor;

    ResetPlayerPositions();

    for (auto const& spawnerObject : m_SpawnerObjects)
    {
        spawnerObject->GetComponent<CreatureSpawner>()->WipeSpawnedCreatures();
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

void Game::GameplaySettingsComponent::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnRoundCompleted")
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
    }
    else
    {
        m_CurrentRound = 0;
        ++m_CurrentLevel;
        
        if (m_CurrentLevel < static_cast<int>(m_Gameplay_Info.LevelsInfo.size()))
        {
            SetupRound(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo[m_CurrentRound]);
        }
    }
}

void Game::GameplaySettingsComponent::Init(std::string const& jsonPath)
{
    json gameplayInfoJSON{ GameEngine::ResourceManager::Get().LoadJSON(jsonPath) };

    m_Gameplay_Info = gameplayInfoJSON.at(0).get<GameplayInfo>();
    UIEngine uiEngine{ m_Gameplay_Info.UIJSONPath };
    GetOwner()->AddComponent<LevelDisplayComponent>();

    SetupPlayers();

    SetupGraphs();
    SetupRound(m_Gameplay_Info.LevelsInfo[m_CurrentLevel].RoundsInfo[m_CurrentRound]);
}

Game::GameplaySettingsComponent::GameplaySettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
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
