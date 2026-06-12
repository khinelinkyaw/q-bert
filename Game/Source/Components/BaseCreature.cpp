#include "BaseCreature.h"

#include <Characters/Breed.h>
#include <Characters/MovementState.h>
#include <Events/EventArgMove.h>
#include <Creatures/SpriteMaps.h>
#include <Misc/Enums.h>

#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Events/EventArgBlock.h>

#include <memory>
#include <utility>

void Game::BaseCreature::Update()
{
    auto newState = m_pMovementState->Update(GetOwner(), m_MoveQueue);

    if (newState)
    {
        m_pMovementState->OnExit();
        m_pMovementState = std::move(newState);
        ChangeSprite(*m_pMovementState);
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
    else if (eventArg->EventId == "IdleEnter")
    {
        if (m_MoveQueue.empty())
        {
            m_pBreed->OnEndOfPath(*GetOwner());
        }
    }
    else if (eventArg->EventId == "OnNewBlock")
    {
        auto newBlockEventArg{ static_cast<EventArgBlock*>(eventArg) };
        m_pBreed->OnNewBlock(*GetOwner(), newBlockEventArg->Block);
    }
     else if (eventArg->EventId == "OnEmptyBlock")
    {
        m_pBreed->OnEmptyBlock(*GetOwner());
    }
}

void Game::BaseCreature::OnCollisionEnter(GameEngine::GameObject* collidingObject) const
{
    if (auto creatureComponent{ collidingObject->GetComponent<BaseCreature>() })
    {
        m_pBreed->OnCollision(*GetOwner(), creatureComponent->GetBreed()->GetWeakness());
    }
}

void Game::BaseCreature::ChangeSprite(MovementState const& movementState)
{
    GetOwner()->GetComponent<GameEngine::SpriteComponent>()->SetSpriteIndex(
        GetSpriteIndexFromMap(*m_pSpriteMap, movementState.GetDirection(), movementState.GetMovementEvent())
    );
}

void Game::BaseCreature::Init(Creature creatureType, PlayerIndex playerIndex)
{
    m_pBreed = std::make_unique<EnemyBreed>();
    m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::DownRight);

    m_pSpriteMap = Sprites::CREATURE_SPRITE_MAP.at(creatureType);

    switch (creatureType)
    {
    case Creature::QBert:
        m_pBreed = std::make_unique<QBertBreed>(GetOwner());
        m_pMovementState = std::make_unique<IdleState>(GetOwner(), Direction::DownRight);
        break;
    case Creature::RedSlime:
        break;
    case Creature::GreenSlime:
    case Creature::Slick:
    case Creature::Sam:
        m_pBreed = std::make_unique<GreenEnemyBreed>();
        break;
    case Creature::PurpleSlime:
        m_pBreed = std::make_unique<PurpleSlimeBreed>();
        break;
    case Creature::Coily:
        break;
    case Creature::Ugg:
        m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::UpLeft);
        break;
    case Creature::WrongWay:
        m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::UpRight);
        break;
    }

    m_pBreed->SetPlayerIndex(playerIndex);
    ChangeSprite(*m_pMovementState);
}

Game::BaseCreature::BaseCreature(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pMovementState{}
{
}
