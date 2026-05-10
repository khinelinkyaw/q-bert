#ifndef NODE_H
#define NODE_H

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
        int m_Id{ INVALID_ID };

    public:
        Block(int id);
    };
}

#endif