#ifndef USER_INTERFACE_FACTORY_H
#define USER_INTERFACE_FACTORY_H

#include <Misc/Constants.h>
#include <Components/ContainerComponent.h>

#include <Engine/Components/SpriteAnimationComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Misc/Types.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace Game
{
    namespace GameplayUI
    {

        float constexpr ROOT_MARGIN{ 20.f };
        float constexpr ELEMENT_PADDING{ 5.f };
        float constexpr ROOT_ELEMENT_WIDTH{ Screen::GAME_WIDTH - (ROOT_MARGIN * 2) };
        float constexpr ROOT_ELEMENT_HEIGHT{ Screen::GAME_HEIGHT - (ROOT_MARGIN * 2) };

        std::string const ROOT_ELEMENT{ "RootUIElement" };
        std::string const PLAYER_1_NAME_ELEMENT{ "Player1NameUIElement" };
        std::string const PLAYER_2_NAME_ELEMENT{ "Player2NameUIElement" };
        std::string const PLAYER_1_SCORE_ELEMENT{ "Player1ScoreUIElement" };
        std::string const LEVEL_TEXT_ELEMENT{ "LevelTextUIElement" };
        std::string const LEVEL_NUM_ELEMENT{ "LevelNumUIElement" };
        std::string const ROUND_TEXT_ELEMENT{ "RoundTextUIElement" };
        std::string const ROUND_NUM_ELEMENT{ "RoundNumUIElement" };
        std::string const CHANGE_TO_TEXT_ELEMENT{ "ChangeToTextUIElement" };
        std::string const CHANGE_TO_BLOCK_ELEMENT{ "ChangeToSpriteUIElement" };
        std::string const RIGHT_ARROWS_ELEMENT{ "RightArrowsUIElement" };
        std::string const LEFT_ARROWS_ELEMENT{ "LeftArrowsUIElement" };
    }

    enum class UIType
    {
        Container,
        Texture,
        Sprite,
        AnimatedSprite,
        SpriteFont
    };

    struct UIComponentInfo
    {
        std::vector<int>            AnimationFrameIndices{};
        std::string                 TextureFilePath{};
        vec2                        ContainerSize{ 0.f, 0.f };
        bool                        FixedPadding{ false };
        Padding                     PaddingSize{ 0.f, 0.f, 0.f, 0.f };
        UIType                      Type{ UIType::Container };
        GameEngine::AnimationType   AnimationType{ GameEngine::AnimationType::Loop };
        float                       AnimationDuration{};
        int                         SpriteIndex{};
        int                         SpriteRows{};
        int                         SpriteCols{};
    };

    struct PositioningInfo
    {
        std::string                 ParentName{};
        GameEngine::Pivot           PivotOnParent{ GameEngine::Pivot::LeftUp };
        GameEngine::Pivot           Pivot{ GameEngine::Pivot::LeftUp };
    };

    struct UIElementInfo
    {
        UIComponentInfo             ComponentInfo{};
        PositioningInfo             PositioningInfo{};
        std::string                 Name{};
    };

    class UIFactory final
    {
    private:
        using ComponentCreationFunction = void(UIFactory::*)(GameEngine::GameObject&, UIComponentInfo const&);

        std::unordered_map<std::string, vec2>                       m_ElementsSizes{};
        //std::unordered_map<std::string, GameEngine::GameObject*>    m_CreatedUIElements{};
        GameEngine::Scene*                                          m_pScene{ GameEngine::SceneManager::Get().GetActiveScene() };

        //void SaveElementSize(GameEngine::Rect<float> const& rect, std::string const& name);
        //void SaveElementSize(std::string const& name, GameEngine::GameObject& gameObject);

        void CreateContainerComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateTextureComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateAnimatedSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteFontComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo);

        std::unordered_map<UIType, ComponentCreationFunction>       m_ComponentCreationFunctions{
            { UIType::Texture,          &UIFactory::CreateTextureComponent },
            { UIType::Sprite,           &UIFactory::CreateSpriteComponent },
            { UIType::AnimatedSprite,   &UIFactory::CreateAnimatedSpriteComponent },
            { UIType::SpriteFont,       &UIFactory::CreateSpriteFontComponent}
        };

        GameEngine::GameObject& CreateRootUIElement();

    public:
        GameEngine::GameObject& CreateUIElement(UIElementInfo const& elementInfo);

        void SetElementPosition(const Game::UIElementInfo& elementInfo, GameEngine::GameObject& uiElement);

        //void CreatePlayer1UIElements(GameEngine::GameObject& parent);
        //void CreateChangeToBlockUIElements();

        UIFactory();
    };
}

#endif