#include "AchievementSystem.h"
#include <Engine/Components/BaseComponent.h>
#include <Engine/Misc/GameObject.h>

#include <string>

#if USE_STEAMWORKS
#pragma warning (push)
#pragma warning (disable:4996)
#include <isteamuserstats.h>
#include <iostream>
#include <isteamuser.h>
#pragma warning (pop)


void Game::AchievementSystem::OnNotify(GameEngine::GameObject&, std::string eventId)
{
    if (eventId == "FirstAchievement")
    {
        SteamUserStats()->SetAchievement("ACH_WIN_100_GAMES");
        SteamUserStats()->StoreStats();
    }
}
Game::AchievementSystem::AchievementSystem()
{
    // Is Steam loaded? If not we can't get stats.
    if (NULL == SteamUserStats() || NULL == SteamUser())
    {
        std::cout << "Steam is not loaded\n";
    }
    // Is the user logged on?  If not we can't access stats.
    if (!SteamUser()->BLoggedOn())
    {
        std::cout << "The user is not logged in\n";
    }
    std::cout << "Achievement system loaded\n";
}
#else

Game::AchievementSystem::AchievementSystem()
{
}

void Game::AchievementSystem::OnNotify(GameEngine::GameObject&, std::string)
{

}
#endif

Game::AchievementComponent::AchievementComponent(GameEngine::GameObject* owner)
    : BaseComponent{owner}
    , m_AchievementSystem{}
{
}
