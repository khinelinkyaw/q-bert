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
        glm::vec3 m_Movement{};
    public:
        void SetMovement(glm::vec3 const& movement) { m_Movement = movement; }
        void Execute(GameEngine::GameObject& gameObject) override;

        MoveCommand(float x = 0.f, float y = 0.f);
    };
}

#endif
