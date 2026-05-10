#include <Engine/Animation/Animation.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/ResourceManager.h>
#include <Engine/Misc/Structs.h>
#include <Engine/Rendering/Renderer.h>

#include <cstdint>
#include <string>

void GameEngine::SpriteComponent::FixedUpdate()
{
}

void GameEngine::SpriteComponent::Update()
{
}

void GameEngine::SpriteComponent::Render(vector3 const&) const
{
}

GameEngine::Rect<float> GameEngine::SpriteComponent::GetSpriteRect(uint8_t index)
{
    if (index < m_TotalSprites)
    {
        return m_SpriteRects[index];
    }

    return Rect<float>();
}

void GameEngine::SpriteComponent::RenderSprite(uint8_t index)
{
    if (m_Texture != nullptr and index < m_TotalSprites)
    {
        auto& renderRect{ m_SpriteRects[index] };
        Renderer::Get().RenderTexture(
            *m_Texture,
            renderRect.x,
            renderRect.y,
            renderRect.width,
            renderRect.height
        );
    }
}

void GameEngine::SpriteComponent::Init(std::string const& filePath, uint8_t rows, uint8_t cols, uint8_t totalSprites)
{
    m_Texture = ResourceManager::Get().LoadTexture(filePath);
    m_Rows = rows;
    m_Cols = cols;
    m_TotalSprites = totalSprites;

    if (m_Texture != nullptr)
    {
        auto spriteSize{ m_Texture->GetSize() };

        auto spriteWidth{ static_cast<int>(spriteSize.x) % cols };
        auto spriteHeight{ static_cast<int>(spriteSize.y) % rows };

        if (m_TotalSprites == 0) m_TotalSprites = rows * cols;

        m_SpriteRects.reserve(m_TotalSprites);

        for (uint8_t rowIdx{}; rowIdx < rows and m_SpriteRects.size() < m_TotalSprites; ++rowIdx)
        {
            for (uint8_t colIdx{}; colIdx < cols and m_SpriteRects.size() < m_TotalSprites; ++colIdx)
            {
                m_SpriteRects.emplace_back(
                    static_cast<float>(spriteWidth * colIdx),
                    static_cast<float>(spriteHeight * rowIdx),
                    static_cast<float>(spriteWidth),
                    static_cast<float>(spriteHeight)
                );
            }
        }
    }
}

GameEngine::SpriteComponent::SpriteComponent(GameObject* owner)
    :BaseComponent{owner}
{
}
