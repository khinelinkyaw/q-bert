#include "Command.h"
#include "Components/ControllerComponent.h"
#include "Minigin.h"
#include "Modules/GameObject.h"
#include "Modules/Transform.h"
#include <glm/ext/vector_common.hpp>

using namespace Engine;

void MoveCommand::Execute(GameObject& gameObject)
{
    glm::vec3 l_MovingDirection{ glm::normalize(m_Movement.GetPosition()) };
    l_MovingDirection *= gameObject.GetComponent<ControllerComponent>()->GetSpeed() * Minigin::GetDeltaTime();
    auto const l_NewPosition{ Transform{l_MovingDirection} + gameObject.GetTransform() };
    gameObject.SetPosition(l_NewPosition);
    m_State = CommandState::Success;
}

MoveCommand::MoveCommand(float x, float y)
    : m_Movement(x, y)
{
}
