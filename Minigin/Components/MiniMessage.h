#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>

namespace GameEngine
{
    typedef std::uint64_t hash_t;

    class MiniMessage final
    {
    private:
        hash_t m_MessageID;
    public:
        hash_t GetID() const { return m_MessageID; }

        MiniMessage(std::string const& str);
        ~MiniMessage() = default;
    };
}

#endif
