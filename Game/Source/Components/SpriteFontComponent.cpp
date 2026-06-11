#include "SpriteFontComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <algorithm>
#include <cassert>

void Game::SpriteFontComponent::Render(vec2 const& pos) const
{
    m_pTextureComponent->Visible = true;

    float offsetX{};
    for (auto iter{ m_Digits.begin() }; iter != m_Digits.end(); ++iter)
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
    m_Digits.clear();

    for (auto character : text)
    {
        if (character >= '0' and character <= '9')
        {
            m_Digits.push_back(character - '0');
        }
        else if (character >= 'A' and character <= 'Z')
        {
            m_Digits.push_back(character - 'A' + 10);
        }
        else if (character >= 'a' and character <= 'z')
        {
            m_Digits.push_back(character - 'a' + 10);
        }
    }
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

        std::ranges::reverse(m_Digits);
    }
}


Game::SpriteFontComponent::SpriteFontComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ GetOwner()->GetComponent<GameEngine::SpriteComponent>() }
    , m_pTextureComponent{ GetOwner()->GetComponent<GameEngine::TextureComponent>() }
{
    assert(m_pSpriteComponent != nullptr);
}
