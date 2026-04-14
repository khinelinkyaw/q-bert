#ifndef FRAME_COUNTER_COMPONENT_H
#define FRAME_COUNTER_COMPONENT_H

#include "BaseComponent.h"
#include <Engine/Components/TextComponent.h>

#include <Engine/Misc/GameObject.h>
#include <glm/fwd.hpp>

namespace GameEngine
{
    class FrameCounterComponent final : public BaseComponent
    {
    private:
        float m_FramesPerSecond{};
        float m_AccumulatedTime{};
        TextComponent m_TextComponent{ this->GetOwnerObject() };

    public:
        void FixedUpdate() override;
        void Update() override;
        void Render(glm::vec3 const& pos) const override;

        FrameCounterComponent(GameObject* owner);
        ~FrameCounterComponent() = default;
        FrameCounterComponent(const FrameCounterComponent& other) = delete;
        FrameCounterComponent(FrameCounterComponent&& other) = delete;
        FrameCounterComponent& operator=(const FrameCounterComponent& other) = delete;
        FrameCounterComponent& operator=(FrameCounterComponent&& other) = delete;

    };
}

#endif
