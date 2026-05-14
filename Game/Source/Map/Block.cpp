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

void Game::Block::CycleType()
{
    switch (m_BlockType)
    {
        case BlockType::Green:
            m_BlockType = BlockType::Blue;
            break;
        case BlockType::Blue:
            m_BlockType = BlockType::Magenta;
            break;
        case BlockType::Magenta:
            m_BlockType = BlockType::Green;
            break;
    }
}

Block::Block(int id, BlockType blockType)
    : m_Id{ id }
    , m_BlockType{ blockType }
{

}
