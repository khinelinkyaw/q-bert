#include "Command.h"

void dae::MoveCommand::Execute()
{
    if (m_pObject)
    {
        auto const NewPosition{ m_Movement + m_pObject->GetTransform() };
        m_pObject->SetPosition(NewPosition.GetPosition().x, NewPosition.GetPosition().y);
    }
}

dae::MoveCommand::MoveCommand(float x, float y)
    : m_Movement(x, y)
{
}
