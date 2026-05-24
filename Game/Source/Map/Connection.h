#ifndef CONNECTION_H
#define CONNECTION_H

#include <Map/Block.h>

#include <utility>

namespace Game
{
    class Connection final
    {
    private:
        int m_FromBlockId{ Block::INVALID_ID };
        int m_ToBlockId{ Block::INVALID_ID };
        float m_Weight{ 1.f };

    public:
        std::pair<int, int> GetConnectionBlocks() const;
        int GetToBlock() const { return m_ToBlockId; }
        int GetFromBlock() const { return m_FromBlockId; }
        float GetWeight() const { return m_Weight; }

        Connection(int fromBlockId, int toBlockId);

        bool operator==(Connection const& other) const;
        bool operator<(Connection const& other) const;
    };
}

#endif