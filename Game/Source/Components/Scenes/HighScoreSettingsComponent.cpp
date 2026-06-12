#include "HighScoreSettingsComponent.h"

#include <Components/Controllers/GeneralInputControllerComponent.h>

Game::HighScoreSettingsComponent::HighScoreSettingsComponent(GameEngine::GameObject* owner)
    : BaseComponent{ owner }
{
    owner->AddComponent<GeneralInputController>();
}
