#include "UIFactory.h"

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

//void Game::UIFactory::CreateContainerComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
//{
//    auto containerComp{ gameObject.AddComponent<ContainerComponent>() };
//
//    auto textureComp{ gameObject.GetComponent<GameEngine::TextureComponent>() };
//
//    Padding padding{};
//    if (componentInfo.FixedPadding)
//    {
//        padding = componentInfo.PaddingSize;
//    }
//    else
//    {
//        padding = componentInfo.PaddingSize * GameplayUI::ELEMENT_PADDING;
//    }
//
//    if (textureComp)
//    {
//        containerComp->Init(*textureComp, componentInfo.PaddingSize);
//    }
//    else
//    {
//        containerComp->Init(
//            { 0.f, 0.f, componentInfo.ContainerSize.x, componentInfo.ContainerSize.y},
//            componentInfo.PaddingSize
//        );
//    }
//}

GameEngine::GameObject& Game::UIFactory::CreateRootUIElement()
{
    auto& object{ m_pScene->CreateGameObject(GameplayUI::ROOT_ELEMENT) };
    object.GetTransform()->SetLocalPosition(GameplayUI::ROOT_MARGIN, GameplayUI::ROOT_MARGIN);
    return object;
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

//void Game::UIFactory::CreatePlayer1UIElements(GameEngine::GameObject& parent)
//{
//    auto& player1TextObj{ m_pScene->CreateGameObject(UI::Names::PLAYER_1_NAME_ELEMENT) };
//    player1TextObj.GetTransform()->SetParent(&parent);
//    player1TextObj.AddComponent<GameEngine::SpriteComponent>()->Init("Player1Text.png", 6, 1);
//    player1TextObj.AddComponent<GameEngine::SpriteAnimationComponent>()->Init(GameEngine::AnimationType::Loop, 0.2f, { 0, 1, 2, 3, 4, 5 });
//    SaveElementSize(player1TextObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::PLAYER_1_NAME_ELEMENT);
//
//    auto& player1ScoreObj{ m_pScene->CreateGameObject(UI::Names::PLAYER_1_SCORE_ELEMENT) };
//    player1ScoreObj.GetTransform()->SetParent(&parent);
//    player1ScoreObj.AddComponent<GameEngine::SpriteComponent>()->Init("OrangeNumbers.png", 1, 10);
//    player1ScoreObj.AddComponent<SpriteFontComponent>()->UpdateNumber(12345);
//    SaveElementSize(player1ScoreObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::PLAYER_1_SCORE_ELEMENT);
//
//    float player1ScoreOffsetY{ m_ElementsSizes[UI::Names::PLAYER_1_NAME_ELEMENT].y + UI::Sizes::ELEMENT_PADDING };
//    player1ScoreObj.GetTransform()->SetLocalPosition(0.f, player1ScoreOffsetY);
//}

//void Game::UIFactory::CreateChangeToBlockUIElements()
//{
//    auto parent{ m_pScene->GetObjectByName(UI::Names::PLAYER_1_SCORE_ELEMENT) };
//
//    auto& changeToTextObj{ m_pScene->CreateGameObject(UI::Names::CHANGE_TO_TEXT_ELEMENT) };
//    changeToTextObj.GetTransform()->SetParent(parent);
//    changeToTextObj.AddComponent<GameEngine::TextureComponent>()->SetTexture("ChangeToText.png");
//    SaveElementSize(changeToTextObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::CHANGE_TO_TEXT_ELEMENT);
//
//    float changeToTextOffsetY{ m_ElementsSizes[UI::Names::PLAYER_1_SCORE_ELEMENT].y + (UI::Sizes::ELEMENT_PADDING * 3) };
//    changeToTextObj.GetTransform()->SetLocalPosition(0.f, changeToTextOffsetY);
//
//    auto& rightArrowsObj{ m_pScene->CreateGameObject(UI::Names::RIGHT_ARROWS_ELEMENT) };
//    rightArrowsObj.GetTransform()->SetParent(&changeToTextObj);
//    rightArrowsObj.AddComponent<GameEngine::SpriteComponent>()->Init("RightArrows.png", 1, 3);
//    rightArrowsObj.AddComponent<GameEngine::SpriteAnimationComponent>()->Init(GameEngine::AnimationType::Loop, 0.5f, { 0, 1, 2 });
//    SaveElementSize(rightArrowsObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::RIGHT_ARROWS_ELEMENT);
//
//    float rightArrowsOffsetY{ m_ElementsSizes[UI::Names::CHANGE_TO_TEXT_ELEMENT].y + UI::Sizes::ELEMENT_PADDING };
//    rightArrowsObj.GetTransform()->SetLocalPosition(0.f, rightArrowsOffsetY);
//
//    auto& changeToBlockObj{ m_pScene->CreateGameObject(UI::Names::CHANGE_TO_BLOCK_ELEMENT) };
//    changeToBlockObj.GetTransform()->SetParent(&rightArrowsObj);
//    auto spriteComp{ changeToBlockObj.AddComponent<GameEngine::SpriteComponent>() };
//    spriteComp->Init("MiniBlocks.png", 3, 3);
//    spriteComp->SetSpriteIndex(0);
//    SaveElementSize(changeToBlockObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::CHANGE_TO_BLOCK_ELEMENT);
//
//    changeToBlockObj.GetTransform()->SetLocalPosition(m_ElementsSizes[UI::Names::RIGHT_ARROWS_ELEMENT].x + UI::Sizes::ELEMENT_PADDING,0.f);
//
//    auto& leftArrowsObj{ m_pScene->CreateGameObject(UI::Names::LEFT_ARROWS_ELEMENT) };
//    leftArrowsObj.GetTransform()->SetParent(&changeToBlockObj);
//    leftArrowsObj.AddComponent<GameEngine::SpriteComponent>()->Init("LeftArrows.png", 1, 3);
//    leftArrowsObj.AddComponent<GameEngine::SpriteAnimationComponent>()->Init(GameEngine::AnimationType::Loop, 0.5f, { 0, 1, 2 });
//    SaveElementSize(leftArrowsObj.GetComponent<GameEngine::TextureComponent>()->GetSourceRect(), UI::Names::LEFT_ARROWS_ELEMENT);
//
//    leftArrowsObj.GetTransform()->SetLocalPosition(m_ElementsSizes[UI::Names::CHANGE_TO_BLOCK_ELEMENT].x + UI::Sizes::ELEMENT_PADDING, 0.f);
//}

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
