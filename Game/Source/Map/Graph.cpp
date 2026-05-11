#include <Map/Block.h>
#include <Map/Connection.h>
#include <Map/Graph.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Components/TextureComponent.h>

#include <algorithm>

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

void Game::Graph::GenerateConnections()
{
}

void Game::Graph::Render(glm::vec3 const& pos) const
{
    for (auto& block : m_Blocks)
    {
        auto textureIter{ m_Textures.find(block.GetType()) };
        if (textureIter != m_Textures.end())
        {
            textureIter->second->Render(pos + glm::vec3(block.GetPosition(), 0.f));
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

glm::vec3 Game::Graph::GetCellCenter(Block const&) const
{
    return glm::vec3();
}

glm::vec3 Game::Graph::GetCellCenter(int ) const
{
    return glm::vec3();
}

Game::Graph::Graph(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    m_Blocks.reserve(m_TotalBlocks);

    int row{ 0 };
    int nextRowIncrement{ row };
    for (int index = 0; index < m_TotalBlocks; ++index)
    {
        m_Blocks.emplace_back(index, BlockType::Green);

        m_Blocks.back().SetPosition(
            (row * BLOCK_SIZE / 2.f) + ((index - nextRowIncrement) * BLOCK_SIZE),
            row * BLOCK_SIZE * 0.75f
        );

        if (index == nextRowIncrement)
        {
            ++row;
            nextRowIncrement += row + 1;
        }
    }

    auto greenTextureComp{ owner->AddComponent<GameEngine::TextureComponent>() };
    greenTextureComp->SetTexture("GreenBlock.png");

    auto blueTextureComp{ owner->AddComponent<GameEngine::TextureComponent>() };
    blueTextureComp->SetTexture("BlueBlock.png");

    auto magentaTextureComp{ owner->AddComponent<GameEngine::TextureComponent>() };
    magentaTextureComp->SetTexture("MagentaBlock.png");

    m_Textures.insert({ BlockType::Green, greenTextureComp });
    m_Textures.insert({ BlockType::Blue, blueTextureComp });
    m_Textures.insert({ BlockType::Magenta, magentaTextureComp });
}
