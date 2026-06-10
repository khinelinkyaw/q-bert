#include <Characters/Breed.h>
#include <Components/BaseCreature.h>
#include <Map/Block.h>
#include <Map/Graph.h>
#include <Misc/Enums.h>
#include <Events/EventArgBlock.h>
#include <Components/ChangeToBlockSetterComponent.h>

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Core/SceneManager.h>
#include <Engine/Components/SpriteComponent.h>
#include <Engine/Components/TextureComponent.h>
#include <Engine/Events/EventArg.h>

#include <algorithm>
#include <utility>
#include <vector>
#include <Engine/Events/EventArgInt.h>

using namespace Game;

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
                auto blockUnderObj{ GetBlock(objPos.x, objPos.y) };

                if (blockUnderObj)
                {
                    obj->SendEvent<EventArgBlock>("OnNewBlock", blockUnderObj);
                }
                else
                {
                    obj->SendEvent<GameEngine::EventArg>("OnEmptyBlock");
                }
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
    m_pTextureComponent->Visible = true;
    for (auto& block : m_Blocks)
    {
        if (block.GetType() == BlockType::Empty) continue;

        auto spriteIndex{ static_cast<int>(block.GetType()) };
        m_pSpriteComponent->SetSpriteIndex(spriteIndex);
        auto blockPos{ block.GetPosition() };
        m_pTextureComponent->Render(pos + vec2{ blockPos.x, blockPos.y });
    }
    m_pTextureComponent->Visible = false;
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

void Graph::SendGraphEvent(GraphEvent graphEvent, ObjectID gameObjectId)
{
    m_EventQueue.push({ graphEvent, gameObjectId });
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

std::pair<Block*, BlockSurface> Game::Graph::GetBlockAndSurface(float worldX, float worldY)
{
    Block* block{ GetBlock(worldX, worldY) };

    if (block)
    {
        auto localPos{ GetOwner()->GetTransform()->GetLocalPosition() };
        float localX{ worldX - localPos.x };
        float localY{ worldY - localPos.y };

        BlockSurface surface{ block->GetCollidingSurface(localX, localY)};

        return { block, surface };
    }

    return { nullptr, BlockSurface::Top };
}

void Game::Graph::Init(BlockType startingBlockType, BlockType finalBlockType)
{
    int row{ 0 };
    int nextRowIncrement{ row };
    for (int index = 0; index < TOTAL_BLOCKS; ++index)
    {
        m_Blocks.emplace_back(index, startingBlockType);

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

    GetOwner()->SendEvent<GameEngine::EventArgInt>("SetChangeToBlock", static_cast<int>(finalBlockType));
}

Graph::Graph(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
    , m_pSpriteComponent{ owner->GetComponent<GameEngine::SpriteComponent>() }
    , m_pTextureComponent{ owner->GetComponent<GameEngine::TextureComponent>() }
{
    if (m_pSpriteComponent == nullptr) m_pSpriteComponent = owner->AddComponent<GameEngine::SpriteComponent>();
    if (m_pTextureComponent == nullptr) m_pTextureComponent = owner->AddComponent<GameEngine::TextureComponent>();

    if (owner->GetComponent<ChangeToBlockSetterComponent>() == nullptr)
    {
        owner->AddComponent<ChangeToBlockSetterComponent>();
    }

    m_pSpriteComponent->Init("Blocks.png", 3, 3);
    m_Blocks.reserve(TOTAL_BLOCKS);
}
