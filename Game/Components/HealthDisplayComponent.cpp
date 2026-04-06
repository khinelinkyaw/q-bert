#include "HealthDisplayComponent.h"
#include <Engine/Components/TextComponent.h>
#include <memory>
#include <Engine/Utils/CompileTimeHashing.h>
#include <Engine/Utils/MiniMessage.h>

void Game::HealthStatusReceiver::HandleMessage(std::unique_ptr<GameEngine::MiniMessage> message)
{

    switch (message->GetID())
    {
    case GameEngine::HashCompileTime("ObjectDamageTaken"):
        break;
    case GameEngine::HashCompileTime("ObjectHealed"):
        break;
    }
}

void Game::HealthStatusReceiver::SetTextPointer(GameEngine::TextComponent* textPtr)
{
    m_TextPtr = textPtr;
}

void Game::HealthDisplayComponent::FixedUpdate()
{
}

void Game::HealthDisplayComponent::Update()
{
}

void Game::HealthDisplayComponent::Render(glm::vec3 const&) const
{
}
