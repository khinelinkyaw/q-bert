#include <Characters/Breed.h>
#include <Components/BaseCreature.h>
#include <Map/Block.h>
#include <Map/Connection.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Rendering/Renderer.h>

#include <algorithm>
#include <utility>
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

std::vector<Block const*> Graph::GetConnectedToBlocks(int blockId) const
{
    std::vector<Block const*> result{};

    if (blockId == Block::INVALID_ID)
    {
        return result;
    }

    for (auto const& connection : m_Connections)
    {
        if (connection.GetFromBlock() == blockId)
        {
            auto toBlock{ GetBlock(connection.GetToBlock()) };
            result.push_back(toBlock);
        }
    }

    return result;
}

std::vector<Block const*> Graph::GetConnectedToBlocks(Block const& block) const
{
    return GetConnectedToBlocks(block.GetId());
}

Block const* Game::Graph::GetBlockInDirection(Block const& block, Direction direction) const
{
    auto nearBlocks{ GetConnectedToBlocks(block) };

    for (auto const& nearBlock : nearBlocks)
    {
        switch (direction)
        {
        case Direction::UpRight:
            if (nearBlock->GetPosition().x > block.GetPosition().x and nearBlock->GetPosition().y < block.GetPosition().y)
            {
                return nearBlock;
            }
            break;
        case Direction::UpLeft:
            if (nearBlock->GetPosition().x < block.GetPosition().x and nearBlock->GetPosition().y < block.GetPosition().y)
            {
                return nearBlock;
            }
            break;
        case Direction::DownRight:
            if (nearBlock->GetPosition().x > block.GetPosition().x and nearBlock->GetPosition().y > block.GetPosition().y)
            {
                return nearBlock;
            }
            break;
        case Direction::DownLeft:
            if (nearBlock->GetPosition().x < block.GetPosition().x and nearBlock->GetPosition().y > block.GetPosition().y)
            {
                return nearBlock;
            }
            break;
        }
    }

    return nullptr;
}

void Graph::HandleEvents()
{
    while (m_EventQueue.empty() == false)
    {
        auto& event{ m_EventQueue.front() };
        auto objId{ event.second };
        auto obj{ GameEngine::SceneManager::Get().GetActiveScene()->GetObjectById(objId) };
        if (obj == nullptr)
        {
            m_EventQueue.pop();
            continue;
        }

        switch (event.first)
        {
            case GraphEvent::EntityMoved:
            {
                auto objPos{ obj->GetTransform()->GetWorldPosition() };
                auto creatureComp{ obj->GetComponent<BaseCreature>() };
                auto blockUnderObj{ GetBlock(objPos.x, objPos.y) };

                if (blockUnderObj == nullptr) creatureComp->GetBreed()->OnEmptyBlock(*obj);
                else creatureComp->GetBreed()->OnNewBlock(blockUnderObj);
                break;
            }
        }

        m_EventQueue.pop();
    }
}

void Graph::Update()
{
    HandleEvents();
}

void Graph::Render(vec2 const& pos) const
{
    for (auto& block : m_Blocks)
    {
        if (auto textureIter{ m_Textures.find(block.GetType()) }; textureIter != m_Textures.end())
        {
            auto texturePtr{ textureIter->second };
            auto blockPos{ block.GetPosition() };

            if (texturePtr != nullptr)
            {
                GameEngine::Renderer::Get().RenderTexture(*texturePtr, pos.x + blockPos.x, pos.y + blockPos.y);
            }
        }
    }
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

Block const* Graph::GetBlock(int blockId) const
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

vec2 Game::Graph::GetBlockSurfaceCenter(int blockId, BlockSurface blockSurface) const
{
    return GetBlockSurfaceCenter(*GetBlock(blockId), blockSurface);
}

vec2 Graph::GetBlockSurfaceCenter(Block const& block, BlockSurface blockSurface) const
{
    return GetOwner()->GetTransform()->GetWorldPosition() + block.GetSurfaceCenter(blockSurface);
}

std::vector<Connection const*> Game::Graph::GetConnectionsFromCell(int blockId) const
{
    std::vector<Connection const*> result{};

    for (auto const& connection : m_Connections)
    {
        if (connection.GetFromBlock() == blockId)
        {
            result.push_back(&connection);
        }
    }

    return result;
}

void Graph::SendGraphEvent(GraphEvent graphEvent, ObjectID gameObjectId)
{
    m_EventQueue.push({ graphEvent, gameObjectId });
}

Block* Graph::GetBlock(int row, int indexInRow)
{
    return GetBlock(GetBlockIdInRow(row, indexInRow));
}

Block const* Game::Graph::GetBlock(float worldX, float worldY) const
{
    auto localPos{ GetOwner()->GetTransform()->GetLocalPosition() };
    float localX{ worldX - localPos.x };
    float localY{ worldY - localPos.y };

    std::vector<Block const*> collidingBlocks{};
    for (auto& block : m_Blocks)
    {
        if (block.IsColliding(localX, localY))
        {
            collidingBlocks.push_back(&block);
        }
    }

    if (collidingBlocks.empty()) return nullptr;

    auto topBlockIter{ std::ranges::max_element(collidingBlocks, std::ranges::greater{}, [](Block const* block)
        {
            return block->GetPosition().z;
        }) };

    return *topBlockIter;
}

Block* Graph::GetBlock(float worldX, float worldY)
{
    return const_cast<Block*>(std::as_const(*this).GetBlock(worldX, worldY));
}

Graph::Graph(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    GameEngine::SceneManager::Get().GetActiveScene()->SetObjectName("Graph", owner->GetId());

    m_Blocks.reserve(TOTAL_BLOCKS);

    int row{ 0 };
    int nextRowIncrement{ row };
    for (int index = 0; index < TOTAL_BLOCKS; ++index)
    {
        m_Blocks.emplace_back(index, BlockType::Green);

        m_Blocks.back().SetPosition(vec3{
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
