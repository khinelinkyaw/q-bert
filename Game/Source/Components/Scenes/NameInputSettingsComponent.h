#ifndef NAME_INPUT_SETTINGS_COMPONENT_H
#define NAME_INPUT_SETTINGS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>
#include <Engine/UI/UIEngine.h>

#include <string>
#include <vector>

namespace Game
{
    class NameInputSettingsComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::UIEngine m_UIEngine{ "JSON/NameInputUI.json" };
        std::vector<GameEngine::GameObject*> const m_CurrentLetterIndicators{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("UpArrowUIElement"),
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("DownArrowUIElement"),
        };

        GameEngine::GameObject* m_NameTextObj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName("NameInputUIElement") };

        std::string m_CurrentName{ "A    " };
        int m_CurrentLetterIndex{ 0 };

        void MoveIndicators(int increment);

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;
        void OnSceneLoad() override;

        NameInputSettingsComponent(GameEngine::GameObject* owner);
        ~NameInputSettingsComponent() override = default;
    };
}

#endif
