#ifndef GRAPH_H
#define GRAPH_H

#include <Map/Block.h>
#include <Map/Connection.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Rendering/Texture2D.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace Game
{
    class Graph final : public GameEngine::BaseComponent
    {
    public:
        static float constexpr BLOCK_SIZE{ 32.f };

    private:
        int m_TotalBlocks{ 28 };
        std::vector<Block> m_Blocks{};
        std::vector<Connection> m_Connections{};
        std::unordered_map<BlockType, std::shared_ptr<GameEngine::Texture2D>> m_Textures{};

        void CreateNewConnection(int fromBlockId, int toBlockId);
        void GenerateConnections();
    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(glm::vec3 const& pos) const override;

        Block* GetBlock(int blockId);
        //Block* GetBlock(int rowIndex, int colIndex);
        //Block* GetBlock(float worldX, float worldY);

        glm::vec3 GetCellCenter(Block const& block) const;
        glm::vec3 GetCellCenter(int blockId) const;

        Graph(GameEngine::GameObject* owner);
        ~Graph() override = default;
    };
}

#endif