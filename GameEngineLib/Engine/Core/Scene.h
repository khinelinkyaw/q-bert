#ifndef SCENE_H
#define SCENE_H

#include <Engine/Core/GameObject.h>
#include <Engine/Misc/Types.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

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

        GameObject* GetObjectById(ObjectID id) const;
        GameObject* GetObjectByName(std::string const& name) const;

        bool SetObjectName(std::string const& name, ObjectID id);

        GameObject& CreateGameObject();

        ~Scene() = default;
        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

    private:
        friend class SceneManager;
        explicit Scene() = default;

        std::unordered_map<std::string, ObjectID> m_NameToIdMap{}; 
        std::vector<std::unique_ptr<GameObject>> m_Objects{};
    };

}  // namespace dae

#endif