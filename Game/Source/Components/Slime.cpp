#include "Slime.h"

#include <Engine/Animation/Animation.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Core/GameObject.h>

#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Misc/Constants.h>

void Game::BaseCreature::Update()
{
    auto newState = m_pMovementState->Update(GetOwner());

    if (newState)
    {
        m_pMovementState->OnExit();
        m_pMovementState = std::move(newState);
        m_pMovementState->OnEnter();
    }
}

void Game::BaseCreature::OnEvent(GameEngine::EventArg* eventArg)
{
    if (eventArg->EventId == "OnMove")
    {
        auto movementEventArg{ static_cast<EventArgMove*>(eventArg) };

        m_pMovementState->SendEvent(movementEventArg->MovementEvent, movementEventArg->Direction);
    }
    else if (eventArg->EventId == "ChangeSprite")
    {
        auto movementEventArg{ static_cast<EventArgMove*>(eventArg) };

        GetOwner()->GetComponent<GameEngine::SpriteComponent>()->SetSpriteIndex(
            GetSpriteIndexFromMap(*m_pSpriteMap, movementEventArg->Direction, movementEventArg->MovementEvent)
        );
    }
}

void Game::BaseCreature::Init(Creature creatureType)
{
    switch (creatureType)
    {
    case Creature::QBert:
        m_pSpriteMap = &Consts::QBERT_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Qbert.png", 1, 8);
        break;
    case Creature::RedSlime:
        m_pSpriteMap = &Consts::RED_SLIME_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
        break;
    case Creature::GreenSlime:
        m_pSpriteMap = &Consts::GREEN_SLIME_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
        break;
    case Creature::PurpleSlime:
        m_pSpriteMap = &Consts::PURPLE_SLIME_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
        break;
    }

    GetOwner()->AddComponent< GameEngine::CollisionComponent>();
    GetOwner()->GetComponent<GameEngine::TextureComponent>()->SetOrigin(0.f, 0.f, GameEngine::Pivot::MiddleDown);
    m_pMovementState->RefreshSprite();
}

Game::BaseCreature::BaseCreature(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pMovementState{ std::make_unique<IdleState>(owner, LookDirection::DownRight) }
{
}
