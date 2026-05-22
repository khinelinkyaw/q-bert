#ifndef SLIME_H
#define SLIME_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Decoupling/Event.h>
#include <Engine/Core/GameObject.h>

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
        PurpleSlime
    };

    class BaseCreature final : public GameEngine::BaseComponent
    {
    private:
        std::unordered_map<int, int> const* m_pSpriteMap{};
        std::unique_ptr<MovementState> m_pMovementState{};

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(glm::vec3 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void Init(Creature creatureType);
        BaseCreature(GameEngine::GameObject* owner);
        ~BaseCreature() override = default;
    };
}

#endif