#include "SpriteFontComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <cassert>
#include <string>

void Game::SpriteFontComponent::Render(vec2 const& pos) const
{
    m_pTextureComponent->Visible = true;

    vec2 offset{ 0.f, 0.f };
    for (auto iter{ m_Text.begin() }; iter != m_Text.end(); ++iter)
    {
        if (*iter >= 0)
        {
            m_pSpriteComponent->SetSpriteIndex(*iter);
            m_pTextureComponent->SetOriginOffset(offset);
            m_pTextureComponent->Render(pos);
        }

        offset.x -= m_pTextureComponent->GetSourceRect().width;

        if (*iter == static_cast<int>(SpecialChars::NewLine))
        {
            offset.x = 0.f;
            offset.y -= m_pTextureComponent->GetSourceRect().height;
        }
    }

    m_pTextureComponent->Visible = false;
}

void Game::SpriteFontComponent::SetText(std::string const& text)
{
    m_Text.clear();

    for (auto character : text)
    {
        if (character >= '0' and character <= '9')
        {
            m_Text.push_back(character - '0');
        }
        else if (character >= 'A' and character <= 'Z')
        {
            m_Text.push_back(character - 'A' + 10);
        }
        else if (character >= 'a' and character <= 'z')
        {
            m_Text.push_back(character - 'a' + 10);
        }
        else if (auto iter { m_CharToIndexMap.find(character)}; iter != m_CharToIndexMap.end())
        {
            m_Text.push_back(iter->second);
        }
    }
}

Game::SpriteFontComponent::SpriteFontComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ GetOwner()->GetComponent<GameEngine::SpriteComponent>() }
    , m_pTextureComponent{ GetOwner()->GetComponent<GameEngine::TextureComponent>() }
{
    assert(m_pSpriteComponent != nullptr);
}
