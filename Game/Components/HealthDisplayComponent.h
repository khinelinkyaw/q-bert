#ifndef HEALTH_DISPLAY_COMPONENT_H
#define HEALTH_DISPLAY_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Receiver.h>
#include <Engine/Components/TextComponent.h>
#include <memory>

namespace Game
{
    class HealthStatusReceiver final : public GameEngine::Receiver
    {
    private:
        GameEngine::TextComponent* m_TextPtr;
    public:
        void HandleMessage(std::unique_ptr<GameEngine::MiniMessage> message);
        void SetTextPointer(GameEngine::TextComponent* textPtr);
    };

    class HealthDisplayComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::TextComponent m_Text;

    public:
#pragma region BaseClassFunctions
        void FixedUpdate();
        void Update();
        void Render(glm::vec3 const&) const;
#pragma endregion
    };
}

#endif
