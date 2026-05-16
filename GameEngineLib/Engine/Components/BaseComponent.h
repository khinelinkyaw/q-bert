#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <Engine/Decoupling/Event.h>
#include <Engine/Core/Macros.h>
#include <glm/fwd.hpp>

#include <type_traits>

namespace GameEngine
{
    using vector3 = glm::vec3;

    class GameObject;

    class BaseComponent
    {
    private:
        GameObject* m_pOwner{};

    public:
        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void Render(vector3 const& pos) const = 0;
        virtual void OnCollisionEnter(GameObject* collidingObject) const;
        virtual void OnCollisionStay(GameObject* collidingObject) const;
        virtual void OnCollisionExit(GameObject* collidingObject) const;
        virtual void OnEvent(EventArg const& eventArg);

        GameObject* GetOwner() const;

        BaseComponent() = delete;
        BaseComponent(GameObject* owner);
        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    };

    template<typename T> concept DerivedComponent = std::is_base_of<BaseComponent, T>::value;
}

#endif
