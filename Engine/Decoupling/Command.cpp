#include <Engine/Decoupling/Command.h>
#include <Engine/Components/ControllerComponent.h>
#include <Engine/Minigin.h>
#include <Engine/Misc/GameObject.h>
#include <Engine/Misc/Transform.h>
#include <Game/Components/PlayerComponent.h>

#include <glm/ext/vector_common.hpp>

using namespace GameEngine;

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

void GameEngine::TakeDamageCommand::Execute(GameObject& gameObject)
{
    auto pHealthComponent{ gameObject.GetComponent<Game::PlayerComponent>() };

    pHealthComponent->TakeDamage();
}
