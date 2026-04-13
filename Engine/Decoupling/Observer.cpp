#include "Observer.h"
//#include <string>
//#include <cassert>

//void GameEngine::Observer::OnNotify(GameObject& gameObject, std::string eventId)
//{
//    assert(m_EventBindings.contains(eventId));
//
//    auto event{ m_EventBindings[eventId] };
//    event(gameObject);
//}

//void GameEngine::Observer::BindEvent(std::string eventId, void(*func)(GameObject&))
//{
//    m_EventBindings.insert({ eventId, func });
//}

//GameEngine::Observer::Observer()
//    : m_EventBindings{}
//{
//}

GameEngine::NullObserver::NullObserver()
    : Observer()
{
}
