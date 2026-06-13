#ifndef LEVEL_DISPLAY_COMPONENT_H
#define LEVEL_DISPLAY_COMPONENT_H

#include <Misc/Constants.h>

#include <Engine/Components/SpriteFontComponent.h>
#include <Engine/UI/UIEngine.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

namespace Game
{
    class LevelDisplayComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::SpriteComponent* m_pChangeToBlockSprite{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::CHANGE_TO_BLOCK_ELEMENT)->GetComponent<GameEngine::SpriteComponent>()
        };

        GameEngine::SpriteFontComponent* m_pLevelNumSpriteFont{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::LEVEL_NUM_ELEMENT)->GetComponent<GameEngine::SpriteFontComponent>()
        };

        GameEngine::SpriteFontComponent* m_pRoundNumSpriteFont{
            GameEngine::SceneManager::Get().GetActiveScene()->GetObjectByName(GameplayUI::ROUND_NUM_ELEMENT)->GetComponent<GameEngine::SpriteFontComponent>()
        };

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void Init(int changeToBlockSpriteIndex, int levelNum, int roundNum);
        LevelDisplayComponent(GameEngine::GameObject* owner);
        ~LevelDisplayComponent() override = default;
    };
}

#endif
