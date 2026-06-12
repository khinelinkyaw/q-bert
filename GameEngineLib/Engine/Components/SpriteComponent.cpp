#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Misc/Structs.h>

#include <string>

void GameEngine::SpriteComponent::SetSpriteIndex(int index)
{
    if (index >= 0 and index < static_cast<int>(m_SpriteRects.size()))
    {
        m_TextureComponent->SetSourceRect(m_SpriteRects[index]);
    }
}

void GameEngine::SpriteComponent::Init(std::string const& filePath, int rows, int cols, int totalSprites)
{
    m_TextureComponent = GetOwner()->GetComponent<TextureComponent>();

    if (m_TextureComponent == nullptr)
    {
        m_TextureComponent = GetOwner()->AddComponent<TextureComponent>();
    }

    m_TextureComponent->SetTexture(filePath);

    auto textureSize{ m_TextureComponent->GetTextureSize() };
    auto spriteWidth{ textureSize.width / cols };
    auto spriteHeight{ textureSize.height / rows };

    if (m_TotalSprites == 0 or m_TotalSprites > rows * cols)
    {
        m_TotalSprites = rows * cols;
    }
    else
    {
        m_TotalSprites = totalSprites;
    }

    m_SpriteRects.reserve(m_TotalSprites);

    for (int rowIndex{ 0 }; rowIndex < rows and static_cast<int>(m_SpriteRects.size()) < m_TotalSprites; ++rowIndex)
    {
        for (int colIndex{ 0 }; colIndex < cols and static_cast<int>(m_SpriteRects.size()) < m_TotalSprites; ++colIndex)
        {
            m_SpriteRects.emplace_back(
                static_cast<float>(spriteWidth * colIndex),
                static_cast<float>(spriteHeight * rowIndex),
                static_cast<float>(spriteWidth),
                static_cast<float>(spriteHeight)
            );
        }
    }

    SetSpriteIndex(0);
}

GameEngine::SpriteComponent::SpriteComponent(GameObject* owner)
    : BaseComponent{owner}
{
}
