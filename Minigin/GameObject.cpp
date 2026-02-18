#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate()
{
	for (auto& component : m_Components)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_Components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();

	if (m_texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	for (const auto& component : m_Components)
	{
		component->Render(pos);
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::RemoveComponent(size_t index)
{
	if (index < m_Components.size())
	{
		m_Components.erase(m_Components.begin() + index);
	}
}
