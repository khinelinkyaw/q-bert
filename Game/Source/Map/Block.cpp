#include <Map/Block.h>

using namespace Game;

int Block::GetId() const
{
    return m_Id;
}

BlockType Block::GetType() const
{
    return m_BlockType;
}

void Block::SetType(BlockType blockType)
{
    m_BlockType = blockType;
}

Block::Block(int id, BlockType blockType)
    : m_Id{ id }
    , m_BlockType{ blockType }
{

}
