#include <Commands/PlayerCommands.h>
#include <Components/ControllerComponent.h>
#include <Components/PlayerComponent.h>

#include <Engine/Decoupling/Command.h>
#include <Engine/Minigin.h>
#include <Engine/Misc/GameObject.h>

using namespace Game;

void MoveCommand::Execute(GameEngine::GameObject& gameObject)
{
    glm::vec3 movingDirection{ glm::normalize(m_Movement) };
    movingDirection *= gameObject.GetComponent<ControllerComponent>()->GetSpeed() * GameEngine::Minigin::GetDeltaTime();
    auto const newPosition{ movingDirection + gameObject.GetTransform()->GetLocalPosition() };
    gameObject.SetPosition(newPosition);
    m_State = GameEngine::CommandState::Success;
}

MoveCommand::MoveCommand(float x, float y)
    : m_Movement{ x, y, 0.f }
{
}

void TakeDamageCommand::Execute(GameEngine::GameObject& gameObject)
{
    auto pPlayerComponent{ gameObject.GetComponent<Game::PlayerComponent>() };

    pPlayerComponent->TakeDamage();
}

void IncreaseScore::Execute(GameEngine::GameObject& gameObject)
{
    auto pPlayerComponent{ gameObject.GetComponent<Game::PlayerComponent>() };

    pPlayerComponent->IncrementScore(10);
}
