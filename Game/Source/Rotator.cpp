#include <cmath>
#include <numbers>

#include "Rotator.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/Minigin.h>

void Game::Rotator::FixedUpdate()
{
    m_CurrentRadian += m_Speed * GameEngine::Minigin::GetFixedTimeStep();

    if (m_CurrentRadian >= 2 * std::numbers::pi)
    {
        m_CurrentRadian = 0;
    }

    m_ObjTransform->SetX((cosf(m_CurrentRadian) * m_Radius) + m_Pivot.x);
    m_ObjTransform->SetY((sinf(m_CurrentRadian) * m_Radius) + m_Pivot.y);
}

void Game::Rotator::Init(glm::vec3 pivot, float radius, float speed)
{
    if (m_ObjTransform == nullptr)
        GetOwnerObject()->GetTransform();

    m_Pivot = pivot;
    m_Radius = radius;
    m_Speed = speed;
}

Game::Rotator::Rotator(GameEngine::GameObject* owner)
    : BaseComponent{owner}
    , m_ObjTransform{owner->GetTransform()}
    , m_Pivot{}
    , m_Radius{}
    , m_CurrentRadian{}
    , m_Speed{}
{
}
