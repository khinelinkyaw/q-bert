#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <glm/fwd.hpp>

namespace GameEngine
{
    using vector3 = glm::vec3;

    class GameObject;

    class BaseComponent
    {
    private:
        GameObject* m_pOwner{};

    protected:
        GameObject* GetOwnerObject() const;

    public:
        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void Render(vector3 const& pos) const = 0;

        BaseComponent() = delete;
        BaseComponent(GameObject* owner);
        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    };
}

#endif
