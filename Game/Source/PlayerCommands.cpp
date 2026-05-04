#include "PlayerCommands.h"

#include <Engine/Misc/GameObject.h>

#include <Components/PlayerComponent.h>

//#include <glm/ext/vector_common.hpp>

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
