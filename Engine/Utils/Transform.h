#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace GameEngine
{
    using glm::vec3;

    class Transform final
    {
    public:
        Transform() = default;
        Transform(vec3 const& position)
            : m_Position(position)
        {
        }
        Transform(float x, float y, float z = 0)
            : m_Position{}
        {
            SetPosition(x, y, z);
        }

        vec3 const& GetPosition() const { return m_Position; }
        void SetPosition(float x, float y, float z = 0);
        void SetPosition(vec3 const& position);

        Transform operator+(Transform const& other)
        {
            Transform result{ m_Position + other.GetPosition() };
            return result;
        }

    private:
        vec3 m_Position;
    };
}

#endif