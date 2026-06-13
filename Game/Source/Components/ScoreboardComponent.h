#ifndef SCOREBOARD_COMPONENT_H
#define SCOREBOARD_COMPONENT_H

#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/Types.h>

#include <string>
#include <utility>
#include <vector>

namespace Game
{
    using PlayerScorePair = std::pair<std::string, int>;

    class ScoreboardComponent final : public GameEngine::BaseComponent
    {
    private:
        std::string const ScoreboardFilePath{ "JSON/Scoreboard.json" };
        std::vector<PlayerScorePair> PlayerScores{};

    public:
        void FixedUpdate() override {};
        void Update() override {};
        void Render(vec2 const&) const override {};
        void OnSceneLoad() override;

        void UpdateScore(std::string name, int score);
        std::vector<PlayerScorePair> GetPlayerScores() const { return PlayerScores; }

        ScoreboardComponent(GameEngine::GameObject* owner);
        ~ScoreboardComponent() override = default;
    };
}

#endif
