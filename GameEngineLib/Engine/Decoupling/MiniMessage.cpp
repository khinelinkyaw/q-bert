#include <Engine/Decoupling/MiniMessage.h>
#include <Engine/Utils/CompileTimeHashing.h>
#include <string>

GameEngine::MiniMessage::MiniMessage(std::string const& str)
    : m_MessageID{ GameEngine::HashString(str.c_str()) }
{
}
