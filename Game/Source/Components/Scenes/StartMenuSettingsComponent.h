#ifndef MAIN_MENU_SETTINGS_COMPONENT_H
#define MAIN_MENU_SETTINGS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <UserInterface/UIEngine.h>

#include <Engine/Misc/Enums.h>
#include <Misc/Enums.h>
#include <unordered_map>

namespace Game
{
    class MainMenuSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        UIEngine m_UIEngine{"JSON/MainMenuUI.json"};

        std::unordered_map<Gamemode, GameEngine::GameObject*> const m_GamemodeNames{
            { Gamemode::Solo,   GameEngine::SceneManager::Get().GetObjectByName("SoloUIElement")},
            { Gamemode::Coop,   GameEngine::SceneManager::Get().GetObjectByName("CoopUIElement") },
            { Gamemode::Versus, GameEngine::SceneManager::Get().GetObjectByName("VersusUIElement") }
        };

        GameEngine::GameObject* m_pSelector{ GameEngine::SceneManager::Get().GetObjectByName("SelectorUIElement") };

        Gamemode m_SelectedGamemode{ Gamemode::Solo };
    public:
        void UpdateSelectorPosition();
        void MoveSelector(GameEngine::Direction direction);

        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        MainMenuSettingsComponent(GameEngine::GameObject* owner);
        ~MainMenuSettingsComponent() override = default;
    };
}

#endif
