#include <Engine/Input/InputDevice.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Input/InputMapping.h>
#include <Engine/Core/ResourceManager.h>

#include <SDL3/SDL_events.h>

#include <memory>
#include <string>
#include <utility>

using namespace GameEngine;

InputMapping* GameEngine::InputManager::AddInputMapping(std::string const& name, std::unique_ptr<InputMapping>&& inputMapping)
{
    auto result{ m_InputMappingMap.insert({ name, std::move(inputMapping) }) };

    if (result.second)
    {
        return result.first->second.get();
    }
    return nullptr;
}

InputMapping* GameEngine::InputManager::GetInputMapping(std::string const& name)
{
    auto inputMappingIter{ m_InputMappingMap.find(name) };

    if (inputMappingIter != m_InputMappingMap.end())
    {
        return inputMappingIter->second.get();
    }

    return nullptr;
}

void GameEngine::InputManager::ImportInputMappingJSON(std::string const& jsonFilePath)
{
    auto jsonData{ ResourceManager::Get().LoadJSON(jsonFilePath) };
    InputMappingJSONData data{ jsonData.at(0).get<InputMappingJSONData>()};

    for (auto const& [inputMappingName, actionMappings] : data)
    {
        std::unique_ptr<InputMapping> inputMapping{ std::make_unique<InputMapping>() };

        for (auto const& [actionName, actionMapping] : actionMappings)
        {
            inputMapping->SetActionMapping(actionName, actionMapping.actionType, actionMapping.keyboardCode, actionMapping.gamepadCode);
        }

        m_InputMappingMap.insert({ inputMappingName, std::move(inputMapping) });
    }
}

GamepadInputDevice& GameEngine::InputManager::GetGamepadInputDevice(int playerIndex)
{
    for (GamepadInputDevice& gamepadInputDevice : m_GamepadInputDevices)
    {
        if (gamepadInputDevice.GetPlayerIndex() == playerIndex)
        {
            return gamepadInputDevice;
        }
    }

    GamepadInputDevice::RefreshGamepads();

    m_GamepadInputDevices.emplace_back(playerIndex);
    return m_GamepadInputDevices.back();
}

bool InputManager::ProcessInput()
{
    m_KeyboardInputDevice.UpdateState();

    for (GamepadInputDevice& gamepadInputDevice : m_GamepadInputDevices)
    {
        gamepadInputDevice.UpdateState();
    }

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            return false;
        }
    }

    return true;
}

GameEngine::InputManager::InputManager()
{
    m_GamepadInputDevices.reserve(4);
}
