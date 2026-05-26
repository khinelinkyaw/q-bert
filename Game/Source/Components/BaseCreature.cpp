#include "BaseCreature.h"

#include <Characters/Breed.h>
#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/Controllers/SlimeController.h>
#include <Misc/Constants.h>
#include <Misc/Enums.h>

#include <Engine/Animation/Animation.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Misc/Enums.h>

#include <memory>
#include <utility>

void Game::BaseCreature::Update()
{
    auto newState = m_pMovementState->Update(GetOwner(), m_MoveQueue);

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

        m_MoveQueue.emplace(movementEventArg->MovementEvent, movementEventArg->Direction, m_Surface);
    }
    if (eventArg->EventId == "IdleEnter")
    {
        if (m_MoveQueue.empty())
        {
            GetOwner()->SendEvent<GameEngine::EventArg>("EndOfPath");
        }
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
    if (creatureType == Creature::RedSlime or creatureType == Creature::GreenSlime or creatureType == Creature::PurpleSlime)
    {
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Slimes.png", 1, 6);
        m_pMovementState = std::make_unique<FallingState>(GetOwner(), Direction::DownRight, m_Surface);
        GetOwner()->AddComponent<SlimeController>()->Init(creatureType);
    }

    if (creatureType != Creature::QBert)
    {
        m_pBreed = std::make_unique<EnemyBreed>();
    }

    switch (creatureType)
    {
    case Creature::QBert:
        m_pSpriteMap = &Consts::QBERT_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Qbert.png", 1, 8);
        m_pMovementState = std::make_unique<IdleState>(GetOwner(), Direction::DownRight, m_Surface);
        m_pBreed = std::make_unique<QBertBreed>(GetOwner());
        break;
    case Creature::RedSlime:
        m_pSpriteMap = &Consts::RED_SLIME_SPRITE_MAP;
        break;
    case Creature::GreenSlime:
        m_pSpriteMap = &Consts::GREEN_SLIME_SPRITE_MAP;
        break;
    case Creature::PurpleSlime:
        m_pSpriteMap = &Consts::PURPLE_SLIME_SPRITE_MAP;
        break;
    case Creature::Coily:
        m_pSpriteMap = &Consts::COILY_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Coily.png", 1, 8);
        m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::DownRight, m_Surface);
        break;
    }

    GetOwner()->AddComponent< GameEngine::CollisionComponent>();
    GetOwner()->GetComponent<GameEngine::TextureComponent>()->SetOrigin(0.f, 0.f, GameEngine::Pivot::MiddleDown);
    m_pMovementState->RefreshSprite();
}

Game::BaseCreature::BaseCreature(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pMovementState{}
{
}
