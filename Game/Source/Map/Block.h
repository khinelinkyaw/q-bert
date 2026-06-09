#ifndef BLOCK_H
#define BLOCK_H

#include <Misc/Enums.h>

#include <Engine/Misc/Types.h>

#include <glm/glm.hpp>

namespace Game
{
    class Block final
    {
    public:
        static int constexpr INVALID_ID{ -1 };
        static float constexpr BLOCK_SIZE{ 32.f };

    private:
        vec3 m_Position{};
        int m_Id{ INVALID_ID };
        BlockType m_BlockType{ BlockType::Yellow };

    public:
        int GetId() const;
        BlockType GetType() const;
        void SetType(BlockType cellType);
        void CycleType();

        vec2 GetSurfaceCenter(BlockSurface blockSurface = BlockSurface::Top) const;
        static constexpr vec2 GetSurfaceOffset(BlockSurface blockSurface);

        void SetPosition(vec3 position) { m_Position = position; }
        void SetPosition(float x, float y) { m_Position = vec3{ x, y, m_Position.z }; }
        vec3 GetPosition() const { return m_Position; }
        vec2 GetPosition2D() const { return vec2{ m_Position.x, m_Position.y }; }

        bool IsColliding(float x, float y) const;
        BlockSurface GetCollidingSurface(float x, float y) const;

        Block(int id, BlockType blockType);

        bool operator==(Block const& other) const
        {
            return m_Id == other.m_Id;
        }
    };
}

#endif