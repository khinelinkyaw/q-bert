#include <Engine/Components/BaseComponent.h>
#include <Engine/Components/TextComponent.h>
#include <Engine/UI/CanvasComponent.h>
#include <memory>
#include <string>
#include <iostream>

GameEngine::TextComponent* GameEngine::CanvasComponent::AddTextComponent(std::string const& id, std::string const& text)
{
    TextComponent* newTextComponent{ new TextComponent{m_pOwner} };
    newTextComponent->SetText(text);
    m_UIComponentMap.insert({ id, std::unique_ptr<TextComponent>{newTextComponent} });
    return newTextComponent;
}

void GameEngine::CanvasComponent::FixedUpdate()
{
}

void GameEngine::CanvasComponent::Update()
{
}

void GameEngine::CanvasComponent::Render(glm::vec3 const&) const
{
}

GameEngine::CanvasComponent::CanvasComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Observer{}
    , m_UIComponentMap{}
{
    m_Observer.BindEvent("Hello", [](int a, int b) { std::cout << (a + b); });
    m_Observer.OnNotify("Hello", 1, 2);
}

//void GameEngine::CanvasObserver::OnNotify(GameObject const& gameObject, std::string eventId)
//{
//    for (auto& [id, textComponent] : m_pCanvasComponent->m_UIComponentMap)
//    {
//        textComponent->OnNotify(gameObject, eventId);
//    }
//}

//GameEngine::CanvasObserver::CanvasObserver(CanvasComponent* pCanvasComponent)
//    : m_pCanvasComponent{pCanvasComponent}
//{
//}
