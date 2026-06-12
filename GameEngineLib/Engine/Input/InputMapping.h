#ifndef INPUT_MAPPING_H
#define INPUT_MAPPING_H

#include <Engine/Misc/Enums.h>

#include <string>
#include <unordered_map>

namespace GameEngine
{
    struct ActionMapping
    {
        InputActionType actionType{ InputActionType::Released};
        InputCode keyboardCode{ InputCode::NONE };
        InputCode gamepadCode{ InputCode::NONE };
    };

    class InputDevice;
    class InputMapping final
    {
    private:
        std::unordered_map<std::string, ActionMapping> m_ActionMappings{};

    public:
        bool GetActionState(std::string const& actionName, InputDevice const& inputDevice) const;

        void SetActionMapping(std::string const& actionName,
                              InputActionType actionType,
                              InputCode keyboardCode = InputCode::NONE,
                              InputCode gamepadCode = InputCode::NONE)
        {
            m_ActionMappings.insert({ actionName, {actionType, keyboardCode, gamepadCode} });
        }
    };
}

#endif
