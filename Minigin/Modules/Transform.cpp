#include "Transform.h"

using namespace GameEngine;

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}
