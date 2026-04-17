#ifndef ROTATOR_H
#define ROTATOR_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TransformComponent.h>

#include <glm/glm.hpp>

namespace Game
{
    class Rotator : public GameEngine::BaseComponent
    {
    private:
        GameEngine::TransformComponent* m_ObjTransform;
        glm::vec3 m_Pivot;
        float m_Radius;
        float m_CurrentRadian;
        float m_Speed;

    public:
        void FixedUpdate();
        void Update() override {};
        void Render(glm::vec3 const&) const {};

        void Init(glm::vec3 pivot, float radius, float speed);

        Rotator(GameEngine::GameObject* owner);
        ~Rotator() override = default;
    };
}

#endif
