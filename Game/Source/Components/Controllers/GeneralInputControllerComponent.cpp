#include "GeneralInputControllerComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Core/ServiceLocator.h>

#include <Misc/GlobalGameSettings.h>

void Game::GeneralInputController::ProcessInput(GameEngine::InputDevice const& inputDevice)
{
    if (m_pInputMapping->GetActionState("SelectorUp", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorUp");
        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(static_cast<int>(SoundEffect::Jump));
    }
    if (m_pInputMapping->GetActionState("SelectorDown", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorDown");
        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(static_cast<int>(SoundEffect::Jump));
    }
    if (m_pInputMapping->GetActionState("SelectorLeft", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorLeft");
    }
    if (m_pInputMapping->GetActionState("SelectorRight", inputDevice))
    {
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorRight");
    }
    if (m_pInputMapping->GetActionState("SelectorConfirm", inputDevice))
    {
        GameEngine::ServiceLocator::Get().GetSoundSystem().Play(static_cast<int>(SoundEffect::Ugg));
        GetOwner()->SendEvent<GameEngine::EventArg>("OnSelectorConfirm");
    }
    if (m_pInputMapping->GetActionState("MuteSound", inputDevice))
    {
        GlobalGameSettings::IsSoundMuted = !GlobalGameSettings::IsSoundMuted;
        GameEngine::ServiceLocator::Get().GetSoundSystem().SetMute(GlobalGameSettings::IsSoundMuted);
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
    AddInputDevice(&GameEngine::InputManager::Get().GetKeyboardInputDevice());
    AddInputDevice(&GameEngine::InputManager::Get().GetGamepadInputDevice(1));
    AddInputDevice(&GameEngine::InputManager::Get().GetGamepadInputDevice(2));
    SetInputMapping(GameEngine::InputManager::Get().GetInputMapping("GeneralInput"));
}
