#include "Transform.h"

using namespace GameEngine;

void OldTransform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void OldTransform::SetPosition(vec3 const& position)
{
	m_Position = position;
}
