#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>

namespace Game
{
    enum class BlockType
    {
        Green,
        Blue,
        Magenta
    };

    class Block final
    {
    public:
        static int constexpr INVALID_ID{ -1 };
    private:
        glm::vec2 m_Position{};
        int m_Id{ INVALID_ID };
        BlockType m_BlockType{ BlockType::Green };

    public:
        int GetId() const;
        BlockType GetType() const;
        void SetType(BlockType cellType);

        void SetPosition(glm::vec2 position) { m_Position = position; }
        void SetPosition(float x, float y) { m_Position = glm::vec2{ x, y }; }
        glm::vec2 GetPosition() const { return m_Position; }

        Block(int id, BlockType blockType);

        bool operator==(Block const& other) const
        {
            return m_Id == other.m_Id;
        }
    };
}

#endif