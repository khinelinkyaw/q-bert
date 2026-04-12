#include <Engine/UI/CanvasComponent.h>
#include <Engine/Components/BaseComponent.h>
#include <string>

//GameEngine::TextComponent& GameEngine::CanvasComponent::AddTextComponent(std::string_view, std::string_view)
//{
//     TODO: insert return statement here
//}

GameEngine::CanvasComponent::CanvasComponent(GameObject* owner)
    : BaseComponent{owner}
    , m_Observer{this}
    , m_UIComponentMap{}
{
}

void GameEngine::CanvasObserver::OnNotify(GameObject& gameObject, std::string eventId)
{
    gameObject;
    eventId;
}

GameEngine::CanvasObserver::CanvasObserver(CanvasComponent* pCanvasComponent)
    : m_pCanvasComponent{pCanvasComponent}
{
}
