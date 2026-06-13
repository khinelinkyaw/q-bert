#ifndef USER_INTERFACE_FACTORY_H
#define USER_INTERFACE_FACTORY_H

#include <Engine/Misc/SerializedStructs.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/Scene.h>
#include <Engine/Core/SceneManager.h>

#include <string>
#include <unordered_map>

namespace GameEngine
{
    class UIEngine final
    {
    private:
        using ComponentCreationFunction = void(UIEngine::*)(GameObject&, UIComponentInfo const&);

        float const ELEMENT_PADDING{ 5.f };

        Scene *const m_pScene{ SceneManager::Get().GetActiveScene() };
        std::unordered_map<UIType, ComponentCreationFunction> const m_ComponentCreationFunctions{
            { UIType::Empty,            &UIEngine::CreateTextureComponent },
            { UIType::Texture,          &UIEngine::CreateTextureComponent },
            { UIType::Sprite,           &UIEngine::CreateSpriteComponent },
            { UIType::AnimatedSprite,   &UIEngine::CreateAnimatedSpriteComponent },
            { UIType::SpriteFont,       &UIEngine::CreateSpriteFontComponent}
        };

        void CreateTextureComponent(GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteComponent(GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateAnimatedSpriteComponent(GameObject& gameObject, UIComponentInfo const& componentInfo);
        void CreateSpriteFontComponent(GameObject& gameObject, UIComponentInfo const& componentInfo);

        void SetElementPosition(const UIElementInfo& elementInfo, GameObject& uiElement);

    public:
        GameObject& CreateUIElement(UIElementInfo const& elementInfo);

        UIEngine(std::string const& UIJSONFilePath);
    };
}

#endif