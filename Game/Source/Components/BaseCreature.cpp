#include "BaseCreature.h"

#include <Characters/Breed.h>
#include <Characters/MovementState.h>
#include <Commands/PlayerCommands.h>
#include <Misc/Constants.h>
#include <Misc/Enums.h>

#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>

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
}

void Game::BaseCreature::ChangeSprite(MovementState const& movementState)
{
    GetOwner()->GetComponent<GameEngine::SpriteComponent>()->SetSpriteIndex(
        GetSpriteIndexFromMap(*m_pSpriteMap, movementState.GetDirection(), movementState.GetMovementEvent())
    );
}

void Game::BaseCreature::Init(Creature creatureType)
{
    m_pBreed = std::make_unique<EnemyBreed>();
    //m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::DownMiddle);
    m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::DownRight);

    switch (creatureType)
    {
    case Creature::QBert:
        m_pSpriteMap = &Consts::QBERT_SPRITE_MAP;
        m_pBreed = std::make_unique<QBertBreed>(GetOwner());
        m_pMovementState = std::make_unique<IdleState>(GetOwner(), Direction::DownRight);
        break;
    case Creature::RedSlime:
        m_pSpriteMap = &Consts::RED_SLIME_SPRITE_MAP;
        break;
    case Creature::GreenSlime:
        m_pSpriteMap = &Consts::GREEN_SLIME_SPRITE_MAP;
        break;
    case Creature::PurpleSlime:
        m_pSpriteMap = &Consts::PURPLE_SLIME_SPRITE_MAP;
        m_pBreed = std::make_unique<PurpleSlimeBreed>();
        break;
    case Creature::Coily:
        m_pSpriteMap = &Consts::COILY_SPRITE_MAP;
        break;
    case Creature::Ugg:
        m_pSpriteMap = &Consts::UGG_SPRITE_MAP;
        m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::UpLeft);
        break;
    case Creature::WrongWay:
        m_pSpriteMap = &Consts::WRONGWAY_SPRITE_MAP;
        m_pMovementState = std::make_unique<IdleWaitState>(GetOwner(), Direction::UpRight);
        break;
    }

    // m_pMovementState->RefreshSprite();
    ChangeSprite(*m_pMovementState);
}

Game::BaseCreature::BaseCreature(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pMovementState{}
{
}
