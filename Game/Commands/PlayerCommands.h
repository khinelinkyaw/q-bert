#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <Engine/Decoupling/Command.h>
#include <Engine/Misc/GameObject.h>

class TakeDamageCommand final : public GameEngine::Command
{
public:
    void Execute(GameEngine::GameObject& gameObject) override;
};

class IncreaseScore final : public GameEngine::Command
{
public:
    void Execute(GameEngine::GameObject& gameObject) override;
};

#endif
