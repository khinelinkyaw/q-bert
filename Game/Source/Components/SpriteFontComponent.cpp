#include "SpriteFontComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <algorithm>
#include <cassert>
#include <string>

void Game::SpriteFontComponent::Render(vec2 const& pos) const
{
    m_pTextureComponent->Visible = true;

    float offsetX{};
    for (auto iter{ m_Text.begin() }; iter != m_Text.end(); ++iter)
    {
        m_pSpriteComponent->SetSpriteIndex(*iter);
        m_pTextureComponent->SetOriginOffset({ offsetX, 0.f });
        m_pTextureComponent->Render(pos);
        offsetX -= m_pTextureComponent->GetSourceRect().width;
    }

    m_pTextureComponent->Visible = false;
}

void Game::SpriteFontComponent::UpdateText(std::string const& text)
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
    }
}

Game::SpriteFontComponent::SpriteFontComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ GetOwner()->GetComponent<GameEngine::SpriteComponent>() }
    , m_pTextureComponent{ GetOwner()->GetComponent<GameEngine::TextureComponent>() }
{
    assert(m_pSpriteComponent != nullptr);
}
