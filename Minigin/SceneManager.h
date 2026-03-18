#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Singleton.h"
#include <memory>
#include <vector>

namespace GameEngine
{
    class Scene;
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene& CreateScene();

        void FixedUpdate();
        void Update();
        void Render();
        void CheckForDeletion();

    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        std::vector<std::unique_ptr<Scene>> m_scenes{};
    };
}

#endif