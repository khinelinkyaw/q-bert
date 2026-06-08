#ifndef SLIME_H
#define SLIME_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <Characters/Breed.h>
#include <Characters/MovementState.h>

#include <memory>
#include <unordered_map>

namespace Game
{
    enum class Creature
    {
        QBert,
        RedSlime,
        GreenSlime,
        PurpleSlime,
        Coily,
        Ugg,
        WrongWay
    };

    class BaseCreature final : public GameEngine::BaseComponent
    {
    private:
        std::unordered_map<int, int> const* m_pSpriteMap{};
        std::unique_ptr<MovementState> m_pMovementState{};
        std::unique_ptr<Breed> m_pBreed{};
        MoveQueue m_MoveQueue{};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec2 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        Breed* GetBreed() const { return m_pBreed.get(); }
        void ChangeSprite(MovementState const& movementState);
        
        void Init(Creature creatureType);
        BaseCreature(GameEngine::GameObject* owner);
        ~BaseCreature() override = default;
    };
}

#endif