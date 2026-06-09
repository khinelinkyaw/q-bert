#include "SpriteFontComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>

#include <cassert>

void Game::SpriteFontComponent::Render(vec2 const& pos) const
{
    m_pTextureComponent->Visible = true;

    float offsetX{};
    for (auto iter{ m_Digits.rbegin() }; iter != m_Digits.rend(); ++iter)
    {
        m_pSpriteComponent->SetSpriteIndex(*iter);
        offsetX -= m_pTextureComponent->GetSrcRect().width;
        m_pTextureComponent->SetOriginOffset({ offsetX, 0.f });
        m_pTextureComponent->Render(pos);
    }

    m_pTextureComponent->Visible = false;
}

void Game::SpriteFontComponent::UpdateNumber(int number)
{
    m_Digits.clear();

    int powerOfTen{ 10 };
    for (int index{ 0 }; index < m_MaxDigits; ++index)
    {
        int digit{ (number % powerOfTen) * 10 / powerOfTen };
        number -= digit;
        powerOfTen *= 10;
        m_Digits.push_back(digit);
    }
}


Game::SpriteFontComponent::SpriteFontComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ GetOwner()->GetComponent<GameEngine::SpriteComponent>() }
    , m_pTextureComponent{ GetOwner()->GetComponent<GameEngine::TextureComponent>() }
{
    assert(m_pSpriteComponent != nullptr);
}
