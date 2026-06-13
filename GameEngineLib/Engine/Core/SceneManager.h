#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <Engine/Core/Scene.h>
#include <Engine/Misc/Singleton.h>
#include <Engine/Misc/Types.h>
#include <Engine/Core/GameObject.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace GameEngine
{
    class Scene;
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene& CreateScene(std::string const& name);

        Scene* GetScene(std::string const& name) const;
        Scene* GetActiveScene() const;

        bool SetActiveScene(std::string const& name);
        bool SetActiveScene(Scene* scene);

        void FixedUpdate();
        void Update();
        void Render();
        void CheckForDeletion();
        void CheckForSceneChange();

    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;

        std::string m_ActiveSceneName{};
        std::string m_PendingActiveSceneName{};
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes{};
        bool m_PendingSceneChange{ false };
    };
}

#endif