#include "UIEngine.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteAnimationComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>
#include <Engine/UI/Utils.h>
#include <Engine/Components/TextureComponent.h>

#include <Components/ContainerComponent.h>
#include <Components/SpriteFontComponent.h>

#include <string>

void Game::UIFactory::CreateTextureComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    auto textureComp{ gameObject.AddComponent<GameEngine::TextureComponent>() };
    switch (componentInfo.Type)
    {
        case UIType::Texture:
        {
            textureComp->SetTexture(componentInfo.TextureFilePath);
            break;
        }
        case UIType::Empty:
        {
            textureComp->SetSourceRect({0.f, 0.f, componentInfo.ContainerSize.x, componentInfo.ContainerSize.y});
            break;
        }
    }
}

void Game::UIFactory::CreateSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>()->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
}

void Game::UIFactory::CreateAnimatedSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>()->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
    gameObject.AddComponent<GameEngine::SpriteAnimationComponent>()->Init(componentInfo.AnimationType, componentInfo.AnimationDuration, componentInfo.AnimationFrameIndices);
}

void Game::UIFactory::CreateSpriteFontComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>()->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
    gameObject.AddComponent<SpriteFontComponent>()->UpdateNumber(0);
}

GameEngine::GameObject& Game::UIFactory::CreateUIElement(UIElementInfo const& elementInfo)
{
    auto& uiElement{ m_pScene->CreateGameObject(elementInfo.Name) };

    if (auto iter{ m_ComponentCreationFunctions.find(elementInfo.ComponentInfo.Type) }; iter != m_ComponentCreationFunctions.end())
    {
        (this->*iter->second)(uiElement, elementInfo.ComponentInfo);
    }

    SetElementPosition(elementInfo, uiElement);
    return uiElement;
}

void Game::UIFactory::SetElementPosition(const Game::UIElementInfo& elementInfo, GameEngine::GameObject& uiElement)
{
    auto parent{ m_pScene->GetObjectByName(elementInfo.PositioningInfo.ParentName) };

    vec2 originPosition{};
    vec2 padding{};

    vec2 multiplers{ GameEngine::UI::GetAxisMultipliers(elementInfo.PositioningInfo.Pivot) };
    if (elementInfo.PositioningInfo.FixedPadding)
    {
        padding = { elementInfo.PositioningInfo.PaddingSize.x * multiplers.x, elementInfo.PositioningInfo.PaddingSize.y * multiplers.y };
    }
    else
    {
        padding = vec2{ elementInfo.PositioningInfo.PaddingSize.x * multiplers.x, elementInfo.PositioningInfo.PaddingSize.y * multiplers.y } * GameplayUI::ELEMENT_PADDING;
    }

    auto elementRect{ uiElement.GetComponent<GameEngine::TextureComponent>()->GetSourceRect() };
    if (parent)
    {
        uiElement.GetTransform()->SetParent(parent);
        Rectf parentRect{ parent->GetComponent<GameEngine::TextureComponent>()->GetSourceRect() };
        auto parentPosition{ GameEngine::UI::AlignToRect(0.f, 0.f, parentRect, elementInfo.PositioningInfo.PivotOnParent) };
        originPosition = parentPosition - GameEngine::UI::AlignToRect(-padding.x, -padding.y, elementRect, elementInfo.PositioningInfo.Pivot);
    }
    else
    {
        originPosition = GameEngine::UI::AlignToWindow(elementInfo.PositioningInfo.Pivot, padding.x, padding.y);
    };

    uiElement.GetTransform()->SetLocalPosition(originPosition);
}

Game::UIFactory::UIFactory()
{
    UIElementInfo rootElementInfo{};
    rootElementInfo.Name = GameplayUI::ROOT_ELEMENT;
    rootElementInfo.ComponentInfo.ContainerSize = { GameplayUI::ROOT_ELEMENT_WIDTH, GameplayUI::ROOT_ELEMENT_HEIGHT };
    rootElementInfo.PositioningInfo.FixedPadding = true;
    rootElementInfo.PositioningInfo.PaddingSize = { GameplayUI::ROOT_MARGIN, GameplayUI::ROOT_MARGIN };

    CreateUIElement(rootElementInfo);

    UIElementInfo player1TextElementInfo{
        UIComponentInfo {
            { 0, 1, 2, 3, 4, 5 },
            "Player1Text.png",
            {0.f,0.f},
            UIType::AnimatedSprite,
            GameEngine::AnimationType::Loop,
            0.2f,
            0,
            6,
            1
        },
        PositioningInfo {
            GameplayUI::ROOT_ELEMENT,
            { 1.f, 1.f },
            GameEngine::Pivot::LeftUp,
            GameEngine::Pivot::LeftUp,
            false,
        },
        GameplayUI::PLAYER_1_NAME_ELEMENT
    };

    CreateUIElement(player1TextElementInfo);

    UIElementInfo player1ScoreElementInfo{
    UIComponentInfo {
        { 0, 1, 2, 3, 4, 5 },
        "OrangeNumbers.png",
        {0.f,0.f},
        UIType::SpriteFont,
        GameEngine::AnimationType::Loop,
        0.2f,
        0,
        1,
        10
    },
    PositioningInfo {
        GameplayUI::PLAYER_1_NAME_ELEMENT,
        { 0.f, 1.f},
        GameEngine::Pivot::LeftDown,
        GameEngine::Pivot::LeftUp,
        false,
    },
    GameplayUI::PLAYER_1_SCORE_ELEMENT
    };

    CreateUIElement(player1ScoreElementInfo);
}
