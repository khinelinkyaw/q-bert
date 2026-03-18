#ifndef HEALTH_DISPLAY_COMPONENT_H
#define HEALTH_DISPLAY_COMPONENT_H

#include <BaseComponent.h>
#include <TextComponent.h>

namespace GameEngine
{
    class MessageQueue;
}

namespace Game
{
    class HealthDisplayComponent final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::MessageQueue* m_MessageQueue;
        GameEngine::TextComponent m_Text;

    public:
#pragma region BaseClassFunctions
        void FixedUpdate();
        void Update();
        void Render(glm::vec3 const& pos) const;
#pragma endregion
    };
}

#endif
