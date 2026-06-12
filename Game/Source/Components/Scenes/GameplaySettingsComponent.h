#ifndef GAMEPLAY_SETTINGS_COMPONENT_H
#define GAMEPLAY_SETTINGS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <Misc/SerializedStructs.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>

#include <string>
#include <vector>

namespace Game
{

    class GameplaySettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::Scene *const m_pScene{ GameEngine::SceneManager::Get().GetActiveScene() };
        Graph* m_pEntityGraph{};
        Graph* m_pDiscGraph{};
        GameEngine::GameObject& m_pPlayer1{ m_pScene->CreateGameObject("Player1") };
        GameEngine::GameObject& m_pPlayer2{ m_pScene->CreateGameObject("Player2") };
        int m_CurrentRound{ 0 };
        int m_CurrentLevel{ 0 };
        GameplayInfo m_Gameplay_Info{};
        std::vector<GameEngine::GameObject*> m_SpawnerObjects{};

        void SetupPlayers();
        void ResetPlayerPositions();
        void SetupRound(RoundInfo const& roundInfo);
        void SetupInputMappings();

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void GoToNextRound();

        Gamemode GetGamemode() const { return m_Gameplay_Info.SelectedGameMode; }

        void Init(std::string const& jsonPath);
        GameplaySettingsComponent(GameEngine::GameObject* owner);
        void SetupGraphs();
    };
}

#endif
