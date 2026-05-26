#ifndef SLIME_H
#define SLIME_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Decoupling/Event.h>

#include <Characters/Breed.h>
#include <Characters/MovementState.h>
#include <Misc/Enums.h>

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
        BlockSurface m_Surface{ BlockSurface::Top };
        MoveQueue m_MoveQueue{};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec3 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        Breed* GetBreed() const { return m_pBreed.get(); }

        void Init(Creature creatureType);
        BaseCreature(GameEngine::GameObject* owner);
        ~BaseCreature() override = default;
    };
}

#endif