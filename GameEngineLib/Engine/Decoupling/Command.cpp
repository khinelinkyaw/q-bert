#include <Engine/Decoupling/Command.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Minigin.h>
#include <Engine/Misc/GameObject.h>

#include <glm/ext/vector_common.hpp>

using namespace GameEngine;

void MoveCommand::Execute(GameObject& gameObject)
{
    vector3 movingDirection{ glm::normalize(m_Movement) };
    movingDirection *= gameObject.GetComponent<ControllerComponent>()->GetSpeed() * Minigin::GetDeltaTime();
    auto const newPosition{ movingDirection + gameObject.GetTransform()->GetLocalPosition() };
    gameObject.SetPosition(newPosition);
    m_State = CommandState::Success;
}

MoveCommand::MoveCommand(float x, float y)
    : m_Movement{ x, y, 0.f }
{
}
