#ifndef CHANGE_TO_BLOCK_SETTER_COMPONENT_H
#define CHANGE_TO_BLOCK_SETTER_COMPONENT_H

#include <UserInterface/UIEngine.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Components/SpriteComponent.h>

namespace Game
{
    class ChangeToBlockSetterComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::SpriteComponent* m_pSpriteComponent{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::CHANGE_TO_BLOCK_ELEMENT)->GetComponent<GameEngine::SpriteComponent>()
        };

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        ChangeToBlockSetterComponent(GameEngine::GameObject* owner);
        ~ChangeToBlockSetterComponent() override = default;
    };
}

#endif