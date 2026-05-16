#include <Components/Qbert.h>
#include <Map/Block.h>
#include <Map/Connection.h>
#include <Map/Graph.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Components/TextureComponent.h>

#include <algorithm>
#include <vector>

using namespace Game;

void Graph::CreateNewConnection(int fromBlockId, int toBlockId)
{
    auto fromBlock{ GetBlock(fromBlockId) };
    auto toBlock{ GetBlock(toBlockId) };

    if (fromBlock == nullptr or toBlock == nullptr)
    {
        return;
    }

    auto newConnection{ Connection{ fromBlockId, toBlockId } };
    if (std::ranges::find(m_Connections, newConnection) != m_Connections.end())
    {
        return;
    }

    m_Connections.push_back(newConnection);
}

void Graph::GenerateConnections()
{
    for (int row{ 0 }; row < TOTAL_ROWS; ++row)
    {
        auto blockIds{ GetBlockIdsInARow(row) };

        for (int index{ 0 }; index < blockIds.size(); ++index)
        {
            CreateNewConnection(blockIds[index], GetBlockIdInRow(row - 1, index));
            CreateNewConnection(blockIds[index], GetBlockIdInRow(row - 1, index - 1));
            CreateNewConnection(blockIds[index], GetBlockIdInRow(row + 1, index));
            CreateNewConnection(blockIds[index], GetBlockIdInRow(row + 1, index + 1));
        }
    }
}

std::vector<int> Graph::GetBlockIdsInARow(int row) const
{
    std::vector<int> result{};

    int firstBlockIdInRow{ ((row * (row + 1)) / 2) };

    for (int index{ 0 }; index <= row; ++index)
    {
        result.push_back(firstBlockIdInRow + index);
    }

    return result;
}

int Graph::GetBlockIdInRow(int row, int indexInRow) const
{
    if (row < 0 or indexInRow > row or indexInRow < 0)
    {
        return Block::INVALID_ID;
    }

    int blockIdInRow{ ((row * (row + 1)) / 2) + indexInRow};

    if (blockIdInRow >= TOTAL_BLOCKS)
    {
        return Block::INVALID_ID;
    }
    return blockIdInRow;
}

std::vector<Block*> Graph::GetConnectedToBlocks(int blockId)
{
    std::vector<Block*> result{};

    if (blockId == Block::INVALID_ID)
    {
        return result;
    }

    for (auto& connection : m_Connections)
    {
        if (connection.GetFromCell() == blockId)
        {
            auto toBlock{ GetBlock(connection.GetToCell()) };
            result.push_back(toBlock);
        }
    }

    return result;
}

std::vector<Block*> Graph::GetConnectedToBlocks(Block const& block)
{
    return GetConnectedToBlocks(block.GetId());
}

void Graph::HandleEvents()
{
    while (m_EventQueue.empty() == false)
    {
        auto& event{ m_EventQueue.front() };

        switch (event.first)
        {
        case GraphEvent::QBertMoved:
            auto qbertObj{ event.second };
            auto qbertPos{ qbertObj->GetTransform()->GetWorldPosition() };
            //auto qBertOrigin{ qbertObj->GetComponent<GameEngine::TextureComponent>()->GetOrigin() };

            auto blockUnderQbert{ GetBlock(qbertPos.x, qbertPos.y) };

            if (blockUnderQbert == nullptr)
            {
                // Player loses a health or dies
                qbertObj->GetTransform()->SetLocalPosition(GetBlockSurfaceCenter(0));
            }
            else
            {
                // Notify block change
                blockUnderQbert->CycleType();
            }

            break;
        }

        m_EventQueue.pop();
    }
}

void Graph::Update()
{
    HandleEvents();
}

void Graph::Render(glm::vec3 const& pos) const
{
    for (auto& block : m_Blocks)
    {
        auto texturePtr{ m_Textures.find(block.GetType())->second };
        auto blockPos{ block.GetPosition() };

        if (texturePtr != nullptr)
        {
            GameEngine::Renderer::Get().RenderTexture(*texturePtr, pos.x + blockPos.x, pos.y + blockPos.y);
        }
    }

    //for (auto& connection : m_Connections)
    //{
    //    auto fromBlock{ GetBlock(connection.GetFromCell()) };
    //    auto toBlock{ GetBlock(connection.GetToCell()) };
    //    if (fromBlock.GetId() != Block::INVALID_ID and toBlock.GetId() != Block::INVALID_ID)
    //    {
    //        GameEngine::Renderer::Get().DrawLine(
    //            pos + fromBlock.GetSurfaceCenter(),
    //            pos + toBlock.GetSurfaceCenter(),
    //            SDL_Color{ 255, 255, 255, 255 }
    //        );
    //    }
    //}
}

Block* Graph::GetBlock(int blockId)
{
    auto iter{ std::ranges::find_if(m_Blocks, [blockId](Block const& block)
    {
        return block.GetId() == blockId;
    }) };

    if (iter != m_Blocks.end())
    {
        return &*iter;
    }

    return nullptr;
}

Block Graph::GetBlock(int blockId) const
{
    auto iter{ std::ranges::find_if(m_Blocks, [blockId](Block const& block)
    {
        return block.GetId() == blockId;
    }) };

    if (iter != m_Blocks.end())
    {
        return *iter;
    }

    return Block{Block::INVALID_ID, BlockType::Green};
}

glm::vec3 Graph::GetBlockSurfaceCenter(int blockId) const
{
    return GetOwner()->GetTransform()->GetLocalPosition() + GetBlock(blockId).GetSurfaceCenter();
}

void Graph::SendEvent(GraphEvent graphEvent, GameEngine::GameObject* pObject)
{
    m_EventQueue.push({ graphEvent, pObject });
}

Block* Graph::GetBlock(int row, int indexInRow)
{
    return GetBlock(GetBlockIdInRow(row, indexInRow));
}

Block* Graph::GetBlock(float worldX, float worldY)
{
    auto localPos{ GetOwner()->GetTransform()->GetLocalPosition() };
    float localX{ worldX - localPos.x };
    float localY{ worldY - localPos.y };

    for (auto& block : m_Blocks)
    {
        if (block.IsCollidingOnSurface(localX, localY))
        {
            return &block;
        }
    }
    return nullptr;
}

Graph::Graph(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    m_Blocks.reserve(TOTAL_BLOCKS);

    int row{ 0 };
    int nextRowIncrement{ row };
    for (int index = 0; index < TOTAL_BLOCKS; ++index)
    {
        m_Blocks.emplace_back(index, BlockType::Green);

        m_Blocks.back().SetPosition(glm::vec3{
            (row * Block::BLOCK_SIZE / 2.f) + ((index - nextRowIncrement) * Block::BLOCK_SIZE) - (Block::BLOCK_SIZE / 2.f),
            row * Block::BLOCK_SIZE * 0.75f,
            static_cast<float>(row)
        });

        if (index == nextRowIncrement)
        {
            ++row;
            nextRowIncrement += row + 1;
        }
    }

    auto greenTextureComp{ GameEngine::ResourceManager::Get().LoadTexture("GreenBlock.png")};
    auto blueTextureComp{ GameEngine::ResourceManager::Get().LoadTexture("BlueBlock.png") };
    auto magentaTextureComp{ GameEngine::ResourceManager::Get().LoadTexture("MagentaBlock.png") };

    m_Textures.insert({ BlockType::Green, greenTextureComp });
    m_Textures.insert({ BlockType::Blue, blueTextureComp });
    m_Textures.insert({ BlockType::Magenta, magentaTextureComp });

    GenerateConnections();
}
