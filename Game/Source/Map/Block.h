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
        static float constexpr BLOCK_SIZE{ 32.f };

    private:
        glm::vec3 m_Position{};
        int m_Id{ INVALID_ID };
        BlockType m_BlockType{ BlockType::Green };

    public:
        int GetId() const;
        BlockType GetType() const;
        void SetType(BlockType cellType);
        void CycleType();

        glm::vec3 GetSurfaceCenter() const { return glm::vec3{ m_Position.x + BLOCK_SIZE / 2.f, m_Position.y + BLOCK_SIZE * 0.25f, m_Position.z }; }

        void SetPosition(glm::vec3 position) { m_Position = position; }
        void SetPosition(float x, float y) { m_Position = glm::vec3{ x, y, m_Position.z }; }
        glm::vec3 GetPosition() const { return m_Position; }

        bool IsCollidingOnSurface(float worldX, float worldY) const
        {
            return worldX >= m_Position.x && worldX <= m_Position.x + BLOCK_SIZE
                && worldY >= m_Position.y && worldY <= m_Position.y + BLOCK_SIZE/2.f;
        }

        Block(int id, BlockType blockType);

        bool operator==(Block const& other) const
        {
            return m_Id == other.m_Id;
        }
    };
}

#endif