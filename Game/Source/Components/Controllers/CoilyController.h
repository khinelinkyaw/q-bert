#ifndef COILY_CONTROLLER_H
#define COILY_CONTROLLER_H

#include <Map/Block.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>
#include <Engine/Decoupling/Event.h>

#include <vector>

namespace Game
{
    class CoilyController final : public GameEngine::BaseComponent
    {
    private:
        GameEngine::GameObject* m_pQBertObject{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec3 const&) const override {};
        void OnEvent(GameEngine::EventArg* eventArg) override;

        void MoveTowardsQBert();

        //void SetPath(std::vector<Block const*> const& path);
   
        CoilyController(GameEngine::GameObject* owner);
        ~CoilyController() override = default;
    };
}

#endif