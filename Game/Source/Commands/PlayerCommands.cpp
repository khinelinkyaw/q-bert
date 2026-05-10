#include <Commands/PlayerCommands.h>
#include <Components/ControllerComponent.h>

#include <Engine/Decoupling/Command.h>
#include <Engine/Core/Minigin.h>
#include <Engine/Core/GameObject.h>

using namespace Game;

void MoveCommand::Execute(GameEngine::GameObject& gameObject)
{
    auto speed{ gameObject.GetComponent<ControllerComponent>()->GetSpeed() };
    //gameObject.GetComponent<PlayerComponent>

    glm::vec3 movingDirection{ glm::normalize(m_Movement) };
    movingDirection *= speed * GameEngine::Minigin::GetDeltaTime();
    auto const newPosition{ movingDirection + gameObject.GetTransform()->GetLocalPosition() };
    gameObject.SetPosition(newPosition);

    m_State = GameEngine::CommandState::Success;
}

MoveCommand::MoveCommand(float x, float y)
    : m_Movement{ x, y, 0.f }
{
}
