#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace dae
{
    class Transform final
    {
    public:
        Transform() = default;
        Transform(const glm::vec3& position)
            : m_Position(position)
        {
        }
        Transform(float x, float y, float z = 0)
            : m_Position{}
        {
            SetPosition(x, y, z);
        }

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(float x, float y, float z = 0);
        void SetPosition(const glm::vec3& position);

        Transform operator+(const Transform& other)
        {
            Transform result{ m_Position + other.GetPosition() };
            return result;
        }

    private:
        glm::vec3 m_Position;
    };
}

#endif