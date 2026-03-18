#include <MiniMessage.h>
#include <CompileTimeHashing.h>
#include <string>

GameEngine::MiniMessage::MiniMessage(std::string const& str)
    : m_MessageID{ HashCompileTime(str.c_str()) }
{
}
