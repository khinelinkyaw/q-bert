#include <Map/Block.h>
#include <Map/Connection.h>

#include <utility>

using namespace Game;

std::pair<int, int> Connection::GetConnectedCells() const
{
    return std::pair<int, int>{m_FromBlockId, m_ToBlockId};
}

Connection::Connection(int fromBlockId, int toBlockId)
    : m_FromBlockId{ fromBlockId }
    , m_ToBlockId{ toBlockId }
{
}

bool Connection::operator==(Connection const& other) const
{
    return m_FromBlockId == other.m_FromBlockId && m_ToBlockId == other.m_ToBlockId;
}

bool Connection::operator<(Connection const& other) const
{
    return m_FromBlockId < other.m_FromBlockId || (m_FromBlockId == other.m_FromBlockId && m_ToBlockId < other.m_ToBlockId);
}
