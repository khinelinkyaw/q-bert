#include <Map/Block.h>

#include <Misc/Enums.h>

using namespace Game;

int Block::GetId() const
{
    return m_Id;
}

BlockType Block::GetType() const
{
    return m_CurrentBlockType;
}

void Block::SetType(BlockType blockType)
{
    m_CurrentBlockType = blockType;
}

void Game::Block::ReverseBlockType()
{
    int changingBlockTypeInt{ static_cast<int>(m_CurrentBlockType) - 1 };
    int startingBlockTypeInt{ static_cast<int>(m_StartingBlockType) };

    if (changingBlockTypeInt >= startingBlockTypeInt)
    {
        m_CurrentBlockType = static_cast<BlockType>(changingBlockTypeInt);
    }
}

void Game::Block::ForwardBlockType()
{
    int changingBlockTypeInt{ static_cast<int>(m_CurrentBlockType) + 1 };
    int finalBlockTypeInt{ static_cast<int>(m_FinalBlockType) };

    if (changingBlockTypeInt <= finalBlockTypeInt)
    {
        m_CurrentBlockType = static_cast<BlockType>(changingBlockTypeInt);
    }
}

vec2 Game::Block::GetSurfaceCenter(BlockSurface blockSurface) const
{
    switch (blockSurface)
    {
        case BlockSurface::Top:
            return { m_Position.x + BLOCK_SIZE * 0.5f, m_Position.y + BLOCK_SIZE * 0.25f };
        case BlockSurface::Left:
            return { m_Position.x + BLOCK_SIZE * 0.25f, m_Position.y + BLOCK_SIZE * 0.625f };
        case BlockSurface::Right:
            return { m_Position.x + BLOCK_SIZE * 0.75f, m_Position.y + BLOCK_SIZE * 0.625f };
    }

    return vec2{};
}

constexpr vec2 Game::Block::GetSurfaceOffset(BlockSurface blockSurface)
{
    switch (blockSurface)
    {
    case BlockSurface::Top:
        return { BLOCK_SIZE * 0.5f, BLOCK_SIZE * 0.25f };
    case BlockSurface::Left:
        return { BLOCK_SIZE * 0.25f, BLOCK_SIZE * 0.625f };
    case BlockSurface::Right:
        return { BLOCK_SIZE * 0.75f, BLOCK_SIZE * 0.625f };
    }

    return vec2{};
}

bool Game::Block::IsColliding(float x, float y) const
{
    return (x > m_Position.x and x < m_Position.x + BLOCK_SIZE) and (y > m_Position.y and y < m_Position.y + BLOCK_SIZE);
}

BlockSurface Game::Block::GetCollidingSurface(float x, float y) const
{
    if (x > m_Position.x and x < m_Position.x + BLOCK_SIZE
        and y > m_Position.y and y < m_Position.y + BLOCK_SIZE * 0.5f)
    {
        return BlockSurface::Top;
    }
    else if (x > m_Position.x and x < m_Position.x + BLOCK_SIZE * 0.5f
            and y > m_Position.y + BLOCK_SIZE * 0.5f and y < m_Position.y + BLOCK_SIZE)
    {
        return BlockSurface::Left;
    }
    else if (x > m_Position.x + BLOCK_SIZE * 0.5f and x < m_Position.x + BLOCK_SIZE
        and y > m_Position.y + BLOCK_SIZE * 0.5f and y < m_Position.y + BLOCK_SIZE)
    {
        return BlockSurface::Right;
    }

    return BlockSurface::Top;
}

Block::Block(int id, BlockType blockType)
    : m_Id{ id }
    , m_CurrentBlockType{ blockType }
    , m_StartingBlockType{ blockType }
{
    m_FinalBlockType = static_cast<BlockType>((static_cast<int>(blockType) + 2));
}
