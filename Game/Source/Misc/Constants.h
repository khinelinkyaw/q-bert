#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <string>

namespace Game
{
    namespace GameplayUI
    {
        std::string const ROOT_ELEMENT{ "RootUIElement" };
        std::string const PLAYER_1_NAME_ELEMENT{ "Player1NameUIElement" };
        std::string const PLAYER_1_NUMBER_ELEMENT{ "Player1NumberUIElement" };
        std::string const PLAYER_1_SCORE_ELEMENT{ "Player1ScoreUIElement" };
        std::string const PLAYER_2_NAME_ELEMENT{ "Player2NameUIElement" };
        std::string const PLAYER_2_NUMBER_ELEMENT{ "Player2NumberUIElement" };
        std::string const PLAYER_2_SCORE_ELEMENT{ "Player2ScoreUIElement" };
        std::string const LEVEL_TEXT_ELEMENT{ "LevelTextUIElement" };
        std::string const LEVEL_NUM_ELEMENT{ "LevelNumUIElement" };
        std::string const ROUND_TEXT_ELEMENT{ "RoundTextUIElement" };
        std::string const ROUND_NUM_ELEMENT{ "RoundNumUIElement" };
        std::string const CHANGE_TO_TEXT_ELEMENT{ "ChangeToTextUIElement" };
        std::string const CHANGE_TO_BLOCK_ELEMENT{ "ChangeToSpriteUIElement" };
        std::string const RIGHT_ARROWS_ELEMENT{ "RightArrowsUIElement" };
        std::string const LEFT_ARROWS_ELEMENT{ "LeftArrowsUIElement" };
    }

    namespace Screen
    {
        int constexpr GAME_WIDTH{ 300 };
        int constexpr GAME_HEIGHT{ 300 };
    }

    namespace Consts
    {
        namespace Enemy
        {
            float constexpr IDLE_DURATION{ 1.f };
            int constexpr   MAX_NORMAL_ENEMY_PATH_SIZE{ 7 };
            int constexpr   MAX_PURPLE_SLIME_PATH_SIZE{ 5 };
        };
    }
}

#endif