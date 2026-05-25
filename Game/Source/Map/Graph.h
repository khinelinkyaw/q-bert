#ifndef GRAPH_H
#define GRAPH_H

#include <Map/Block.h>
#include <Map/Connection.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>
#include <Engine/Rendering/Texture2D.h>

#include <glm/fwd.hpp>

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

namespace Game
{
    enum class GraphEvent
    {
        EntityMoved
    };

    class Graph final : public GameEngine::BaseComponent
    {
    public:
        static int constexpr TOTAL_BLOCKS{ 28 };
        static int constexpr TOTAL_ROWS{ 7 };

    private:
        std::vector<Block> m_Blocks{};
        std::vector<Connection> m_Connections{};
        std::unordered_map<BlockType, std::shared_ptr<GameEngine::Texture2D>> m_Textures{};
        std::queue<std::pair<GraphEvent, ObjectID>> m_EventQueue{};

        void CreateNewConnection(int fromBlockId, int toBlockId);
        void GenerateConnections();

        std::vector<int> GetBlockIdsInARow(int row) const;
        int GetBlockIdInRow(int row, int indexInRow) const;
        std::vector<Block*> GetConnectedToBlocks(int blockId);
        std::vector<Block*> GetConnectedToBlocks(Block const& block);

        void HandleEvents();

    public:
        void FixedUpdate() override {};
        void Update() override;
        void Render(vec3 const& pos) const override;

        Block* GetBlock(int blockId);
        Block GetBlock(int blockId) const;
        Block* GetBlock(int row, int indexInRow);
        Block* GetBlock(float worldX, float worldY);

        vec3 GetBlockSurfaceCenter(int blockId) const;

        std::vector<Connection const*> GetConnectionsFromCell(int blockId) const;

        void SendEvent(GraphEvent graphEvent, ObjectID gameObjectId);

        Graph(GameEngine::GameObject* owner);
        ~Graph() override = default;
    };
}

#endif