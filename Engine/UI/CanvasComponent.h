#ifndef CANVAS_COMPONENT_H
#define CANVAS_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Observer.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    class GameObject;
    class TextComponent;

    class CanvasComponent final : public BaseComponent
    {
    private:
        //CanvasObserver m_Observer;
        Observer<int, int> m_Observer;
        std::unordered_map<std::string, std::unique_ptr<TextComponent>> m_UIComponentMap;

    public:
        TextComponent* AddTextComponent(std::string const& id, std::string const& text);

        void FixedUpdate() override;
        void Update();
        void Render(glm::vec3 const& pos) const;

        CanvasComponent(GameObject* owner);
        ~CanvasComponent() override = default;

    };
}

#endif