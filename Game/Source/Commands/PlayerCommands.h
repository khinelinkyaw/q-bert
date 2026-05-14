#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <Characters/MovementState.h>

#include <Engine/Decoupling/Command.h>
#include <Engine/Core/GameObject.h>

namespace Game
{
    class MoveCommand final : public GameEngine::Command
    {
    private:
        MovementEvent m_MovementEvent{};
        FacingDir m_Direction{};

    public:
        void Execute(GameEngine::GameObject& gameObject) override;

        MoveCommand(MovementEvent movementEvent, FacingDir direction);
    };
}

#endif
