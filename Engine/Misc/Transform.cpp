#include "Transform.h"

using namespace GameEngine;

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Transform::SetPosition(vec3 const& position)
{
	m_Position = position;
}
