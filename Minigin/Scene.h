#pragma once
#include <memory>
#include <vector>

#include "Modules/GameObject.h"

namespace GameEngine
{
    class Scene final
    {
    public:
        void Add(std::unique_ptr<GameObject> object);
        void Remove(const GameObject& object);
        void RemoveAll();

        void FixedUpdate();
        void Update();
        void Render() const;
        void CheckForDeletion();

        ~Scene() = default;
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

    private:
        friend class SceneManager;
        explicit Scene() = default;

        std::vector<std::unique_ptr<GameObject>> m_Objects{};
    };

}  // namespace dae
