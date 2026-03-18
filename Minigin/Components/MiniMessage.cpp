#include <MiniMessage.h>
#include <CompileTimeHashing.h>
#include <string>

GameEngine::MiniMessage::MiniMessage(std::string const& str)
    : m_MessageID{ HashString(str.c_str()) }
{
}
