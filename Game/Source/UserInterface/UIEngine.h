#ifndef USER_INTERFACE_FACTORY_H
#define USER_INTERFACE_FACTORY_H

#include <Misc/Constants.h>
#include <Misc/Structs.h>
#include <Misc/SerializedStructs.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>

#include <string>
#include <unordered_map>

namespace Game
{
    namespace GameplayUI
    {;
        float constexpr ROOT_MARGIN{ 20.f };
        float constexpr ELEMENT_PADDING{ 5.f };
        float constexpr ROOT_ELEMENT_WIDTH{ Screen::GAME_WIDTH - (ROOT_MARGIN * 2) };
        float constexpr ROOT_ELEMENT_HEIGHT{ Screen::GAME_HEIGHT - (ROOT_MARGIN * 2) };

        std::string const ROOT_ELEMENT{ "RootUIElement" };
        std::string const PLAYER_1_NAME_ELEMENT{ "Player1NameUIElement" };
        std::string const PLAYER_1_NUMBER_ELEMENT{ "Player1NumberUIElement" };
        std::string const PLAYER_1_SCORE_ELEMENT{ "Player1ScoreUIElement" };
        std::string const PLAYER_2_NAME_ELEMENT{ "Player2NameUIElement" };
        std::string const PLAYER_2_NUMBER_ELEMENT{ "Player2NumberUIElement" };
        std::string const PLAYER_2_SCORE_ELEMENT{ "Player2ScoreUIElement" };
        std::string const LEVEL_TEXT_ELEMENT{ "LevelTextUIElement" };
        std::string const LEVEL_NUM_ELEMENT{ "LevelNumUIElement" };
        std::string const ROUND_TEXT_ELEMENT{ "RoundTextUIElement" };
        std::string const ROUND_NUM_ELEMENT{ "RoundNumUIElement" };
        std::string const CHANGE_TO_TEXT_ELEMENT{ "ChangeToTextUIElement" };
        std::string const CHANGE_TO_BLOCK_ELEMENT{ "ChangeToSpriteUIElement" };
        std::string const RIGHT_ARROWS_ELEMENT{ "RightArrowsUIElement" };
        std::string const LEFT_ARROWS_ELEMENT{ "LeftArrowsUIElement" };
    }

    class UIEngine final
    {
    private:
        using ComponentCreationFunction = void(UIEngine::*)(GameEngine::GameObject&, UIComponentInfo const&);

        GameEngine::Scene *const m_pScene{ GameEngine::SceneManager::Get().GetActiveScene() };
        std::unordered_map<UIType, ComponentCreationFunction> const m_ComponentCreationFunctions{
            { UIType::Empty,            &UIEngine::CreateTextureComponent },
            { UIType::Texture,          &UIEngine::CreateTextureComponent },
            { UIType::Sprite,           &UIEngine::CreateSpriteComponent },
            { UIType::AnimatedSprite,   &UIEngine::CreateAnimatedSpriteComponent },
            { UIType::SpriteFont,       &UIEngine::CreateSpriteFontComponent}
        };

        void CreateTextureComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateAnimatedSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteFontComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);

        void SetElementPosition(const Game::UIElementInfo& elementInfo, GameEngine::GameObject& uiElement);

    public:
        GameEngine::GameObject& CreateUIElement(UIElementInfo const& elementInfo);

        UIEngine(std::string const& UIJSONFilePath);
    };
}

#endif