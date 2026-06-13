#include "ScoreboardComponent.h"

#include <Engine/Components/BaseComponent.h>
#include <Engine/Core/ResourceManager.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

void Game::ScoreboardComponent::OnSceneLoad()
{
    auto jsonData{ GameEngine::ResourceManager::Get().LoadJSON(ScoreboardFilePath) };
    PlayerScores = jsonData.get<std::vector<PlayerScorePair>>();
}

void Game::ScoreboardComponent::UpdateScore(std::string name, int score)
{
    if (auto iter{ std::ranges::find_if(PlayerScores, [&name](PlayerScorePair const& player) { return player.first == name; }) }; iter != PlayerScores.end())
    {
        if (iter->second < score)
        {
            iter->second = score;
        }
    }
    else
    {
        PlayerScores.push_back({ name, score });
    }

    GameEngine::ResourceManager::Get().SaveJSON(ScoreboardFilePath, PlayerScores);
}

Game::ScoreboardComponent::ScoreboardComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
}
