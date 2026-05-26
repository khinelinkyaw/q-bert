#include <Map/Block.h>

#include <Misc/Enums.h>

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

vec3 Game::Block::GetSurfaceCenter(BlockSurface blockSurface) const
{
    vec3 result{};
    switch (blockSurface)
    {
        case BlockSurface::Top:
            result = { m_Position.x + BLOCK_SIZE * 0.5f, m_Position.y + BLOCK_SIZE * 0.25f, m_Position.z };
            break;
        case BlockSurface::Left:
            result = { m_Position.x + BLOCK_SIZE * 0.25f, m_Position.y + BLOCK_SIZE * 0.625f, m_Position.z };
            break;
        case BlockSurface::Right:
            result = { m_Position.x + BLOCK_SIZE * 0.75f, m_Position.y + BLOCK_SIZE * 0.625f, m_Position.z };
            break;
    }

    return result;
}

bool Game::Block::IsCollidingOnSurface(float worldX, float worldY, BlockSurface blockSurface) const
{
    switch (blockSurface)
    {
        case BlockSurface::Top:
            return (worldX > m_Position.x and worldX < m_Position.x + BLOCK_SIZE
                and worldY > m_Position.y and worldY < m_Position.y + BLOCK_SIZE * 0.5f);
        case BlockSurface::Left:
            return (worldX > m_Position.x and worldX < m_Position.x + BLOCK_SIZE * 0.5f
                and worldY > m_Position.y + BLOCK_SIZE * 0.5f and worldY < m_Position.y + BLOCK_SIZE);
        case BlockSurface::Right:
            return (worldX > m_Position.x + BLOCK_SIZE * 0.5f and worldX < m_Position.x + BLOCK_SIZE
                and worldY > m_Position.y + BLOCK_SIZE * 0.5f and worldY < m_Position.y + BLOCK_SIZE);
    }

    return false;
}

Block::Block(int id, BlockType blockType)
    : m_Id{ id }
    , m_BlockType{ blockType }
{

}
