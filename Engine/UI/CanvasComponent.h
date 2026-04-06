#ifndef CANVAS_COMPONENT_H
#define CANVAS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Engine/Decoupling/Observer.h>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace GameEngine
{
    class CanvasComponent;
    class CanvasObserver final : public Observer
    {
    private:
        CanvasComponent* m_pCanvasComponent;
    public:
        void OnNotify(GameObject const& gameObject, std::string eventId) override;

        CanvasObserver(CanvasComponent* pCanvasComponent);
        ~CanvasObserver() override = default;
    };

    class CanvasComponent final : public BaseComponent
    {
    private:
        CanvasObserver m_Observer;
        std::unordered_map<std::string, std::unique_ptr<TextComponent>> m_UIComponentMap;

    public:
        //TextComponent& AddTextComponent(std::string_view id, std::string_view text);

        CanvasComponent(GameObject* owner);
        ~CanvasComponent() override = default;
    };
}

#endif