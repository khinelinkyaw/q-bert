#include <Commands/PlayerCommands.h>
#include <Components/PlayerComponent.h>

#include <Engine/Misc/GameObject.h>

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
