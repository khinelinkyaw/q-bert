#include "BaseCreature.h"

#include <Characters/Breed.h>
#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Components/SlimeController.h>
#include <Misc/Constants.h>

#include <Engine/Animation/Animation.h>
#include <Engine/Components/CollisionComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Misc/Enums.h>
#include <Engine/Components/BaseComponent.h>

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

        m_MoveQueue.emplace(movementEventArg->MovementEvent, movementEventArg->Direction);
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
        m_pMovementState = std::make_unique<FallingState>(GetOwner(), LookDirection::DownRight);
        GetOwner()->AddComponent<SlimeController>()->Init(creatureType);
    }

    switch (creatureType)
    {
    case Creature::QBert:
        m_pSpriteMap = &Consts::QBERT_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Qbert.png", 1, 8);
        m_pMovementState = std::make_unique<IdleState>(GetOwner(), LookDirection::DownRight);
        m_pBreed = std::make_unique<QBertBreed>();
        break;
    case Creature::RedSlime:
        m_pSpriteMap = &Consts::RED_SLIME_SPRITE_MAP;
        m_pBreed = std::make_unique<RedSlimeBreed>();
        break;
    case Creature::GreenSlime:
        m_pSpriteMap = &Consts::GREEN_SLIME_SPRITE_MAP;
        m_pBreed = std::make_unique<RedSlimeBreed>();
        break;
    case Creature::PurpleSlime:
        m_pSpriteMap = &Consts::PURPLE_SLIME_SPRITE_MAP;
        m_pBreed = std::make_unique<PurpleSlimeBreed>();
        break;
    case Creature::Coily:
        m_pSpriteMap = &Consts::COILY_SPRITE_MAP;
        GetOwner()->AddComponent<GameEngine::SpriteComponent>()->Init("Coily.png", 1, 8);
        m_pMovementState = std::make_unique<IdleState>(GetOwner(), LookDirection::DownRight);
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
