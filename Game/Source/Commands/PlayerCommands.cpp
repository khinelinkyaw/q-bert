#include <Commands/PlayerCommands.h>
#include <Characters/MovementState.h>
#include <Components/Qbert.h>

#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Command.h>

using namespace Game;

void MoveCommand::Execute(GameEngine::GameObject& gameObject)
{
    gameObject.GetComponent<QBert>()->SendEvent(m_MovementEvent);
    m_State = GameEngine::CommandState::Success;
}

Game::MoveCommand::MoveCommand(MovementEvent movementEvent)
    : m_MovementEvent{ movementEvent }
{
}
