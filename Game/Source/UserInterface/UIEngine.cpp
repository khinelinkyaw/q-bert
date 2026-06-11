#include "UIEngine.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteAnimationComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Misc/Types.h>
#include <Engine/UI/Utils.h>

#include <Components/SpriteFontComponent.h>

#include <Misc/Structs.h>
#include <string>
#include <vector>

void Game::UIEngine::CreateTextureComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
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

void Game::UIEngine::CreateSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    auto spriteComp{ gameObject.AddComponent<GameEngine::SpriteComponent>() };
    spriteComp->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
    spriteComp->SetSpriteIndex(componentInfo.SpriteIndex);
}

void Game::UIEngine::CreateAnimatedSpriteComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>()->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
    gameObject.AddComponent<GameEngine::SpriteAnimationComponent>()->Init(componentInfo.AnimationType, componentInfo.AnimationDuration, componentInfo.AnimationFrameIndices);
}

void Game::UIEngine::CreateSpriteFontComponent(GameEngine::GameObject& gameObject, UIComponentInfo const& componentInfo)
{
    gameObject.AddComponent<GameEngine::TextureComponent>();
    gameObject.AddComponent<GameEngine::SpriteComponent>()->Init(componentInfo.TextureFilePath, componentInfo.SpriteRows, componentInfo.SpriteCols);
    auto spriteFontComp{ gameObject.AddComponent<SpriteFontComponent>() };
    spriteFontComp->UpdateMaxDigit(componentInfo.DigitNum);
    spriteFontComp->UpdateNumber(0);
}

GameEngine::GameObject& Game::UIEngine::CreateUIElement(UIElementInfo const& elementInfo)
{
    auto& uiElement{ m_pScene->CreateGameObject(elementInfo.Name) };

    if (auto iter{ m_ComponentCreationFunctions.find(elementInfo.ComponentInfo.Type) }; iter != m_ComponentCreationFunctions.end())
    {
        (this->*iter->second)(uiElement, elementInfo.ComponentInfo);
    }

    SetElementPosition(elementInfo, uiElement);
    return uiElement;
}

void Game::UIEngine::SetElementPosition(const Game::UIElementInfo& elementInfo, GameEngine::GameObject& uiElement)
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
    elementRect.x = 0.f;
    elementRect.y = 0.f;

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

Game::UIEngine::UIEngine(std::string const& UIJSONFilePath)
{
    json uiElementsInfoJSON{ GameEngine::ResourceManager::Get().LoadJSON(UIJSONFilePath) };

    std::vector<UIElementInfo> uiElementsInfo{ uiElementsInfoJSON.at(0).get<std::vector<UIElementInfo>>() };

    for (const auto& elementInfo : uiElementsInfo)
    {
        CreateUIElement(elementInfo);
    }
}
