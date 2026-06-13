#ifndef MAIN_MENU_SETTINGS_COMPONENT_H
#define MAIN_MENU_SETTINGS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>
#include <Engine/UI/UIEngine.h>

#include <Misc/Constants.h>
#include <Misc/Enums.h>

#include <utility>
#include <vector>

namespace Game
{
    class StartMenuSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::UIEngine m_UIEngine{"JSON/StartMenuUI.json", Screen::GAME_WIDTH, Screen::GAME_HEIGHT };

        std::vector<std::pair<Gamemode, GameEngine::GameObject*>> const m_SelectionElements{
            { Gamemode::Solo,   GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("SoloUIElement")},
            { Gamemode::Coop,   GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("CoopUIElement") },
            { Gamemode::Versus, GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("VersusUIElement") }
        };

        GameEngine::GameObject* m_pSelector{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("SelectorUIElement") };
        int m_Selection{ 0 };

        void MoveSelector(int increment);

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        StartMenuSettingsComponent(GameEngine::GameObject* owner);
        ~StartMenuSettingsComponent() override = default;
    };
}

#endif
