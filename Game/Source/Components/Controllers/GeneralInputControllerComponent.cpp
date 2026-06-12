#include "GeneralInputControllerComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>


void Game::GeneralInputController::ProcessInput(GameEngine::InputDevice const& inputDevice)
{
    if (m_pInputMapping->GetActionState("SelectorUp", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorUp");
    }
    if (m_pInputMapping->GetActionState("SelectorDown", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorDown");
    }
    if (m_pInputMapping->GetActionState("SelectorConfirm", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorConfirm");
    }
    if (m_pInputMapping->GetActionState("MuteSound", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnMuteSound");
    }
    if (m_pInputMapping->GetActionState("SkipRound", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSkipRound");
    }
}

void Game::GeneralInputController::Update()
{
    for (auto inputDevice : m_InputDevices)
    {
        if (inputDevice != nullptr)
        {
            ProcessInput(*inputDevice);
        }
    }
}

void Game::GeneralInputController::AddInputDevice(GameEngine::InputDevice* inputDevice)
{
    m_InputDevices.push_back(inputDevice);
}

Game::GeneralInputController::GeneralInputController(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
