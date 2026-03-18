#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <glm/fwd.hpp>

namespace GameEngine
{
    class GameObject;
    class BaseComponent
    {
    protected:
        GameObject* m_pOwner{};
    public:
        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void Render(glm::vec3 const& pos) const = 0;

        void SetOwner(GameObject* pOwner);

        BaseComponent() = default;
        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    };
}

#endif
