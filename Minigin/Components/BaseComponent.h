#pragma once
#include <glm/fwd.hpp>

namespace dae
{
    class GameObject;
    class BaseComponent
    {
    private:
        GameObject* m_pOwner{};
    public:
        virtual void FixedUpdate() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Render(glm::vec3 const& pos) const = 0;

        virtual void SetOwner(GameObject* pOwner);

        BaseComponent() = default;
        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    };
}
