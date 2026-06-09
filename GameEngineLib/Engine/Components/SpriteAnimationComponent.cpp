#include "SpriteAnimationComponent.h"

#include <Engine/Core/Time.h>
#include <Engine/Components/SpriteComponent.h>

void GameEngine::SpriteAnimationComponent::Update()
{
    if (m_FrameIndices.empty()) return;

    m_ElapsedTime += GameEngine::GetDeltaTime();

    if (m_ElapsedTime >= m_FrameDuration)
    {
        m_CurrentFrame = ++m_CurrentFrame % m_FrameIndices.size();
        m_pSpriteComponent->SetSpriteIndex(m_FrameIndices[m_CurrentFrame]);

        if (not (m_AnimationType == AnimationType::Once and m_CurrentFrame == m_FrameIndices.size() - 1))
        {
            m_ElapsedTime -= m_FrameDuration;
        }
    }
}

void GameEngine::SpriteAnimationComponent::Init(AnimationType animationType, float frameDuration, std::vector<int> const& frameIndices)
{
    m_AnimationType = animationType;
    m_FrameDuration = frameDuration;
    m_FrameIndices = frameIndices;
}

GameEngine::SpriteAnimationComponent::SpriteAnimationComponent(GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ owner->GetComponent<SpriteComponent>() }
{
    assert(m_pSpriteComponent != nullptr);
}
