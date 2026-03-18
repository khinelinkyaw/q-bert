#include "HealthDisplayComponent.h"
#include <TextComponent.h>
#include <memory>
#include <MiniMessage.h>
#include <CompileTimeHashing.h>

void Game::HealthStatusReceiver::HandleMessage(std::unique_ptr<GameEngine::MiniMessage> message)
{
    switch (message->GetID())
    {
    case "ObjectDamageTaken"_hash:
        break;
    case "ObjectHealed"_hash:
        break;
    }
}

void Game::HealthStatusReceiver::SetTextPointer(GameEngine::TextComponent* textPtr)
{
    m_TextPtr = textPtr;
}
