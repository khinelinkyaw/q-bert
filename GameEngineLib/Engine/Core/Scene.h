#ifndef SCENE_H
#define SCENE_H

#include <Engine/Core/GameObject.h>
#include <Engine/Events/EventArg.h>
#include <Engine/Misc/Types.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace GameEngine
{
    class Scene final
    {
    public:
        void Add(std::unique_ptr<GameObject> object);
        void Remove(const GameObject& object);
        void RemoveAll();

        void Load();
        void FixedUpdate();
        void Update();
        void Render() const;
        void CheckForDeletion();

        GameObject* GetObjectById(ObjectID id) const;
        GameObject* GetObjectByName(std::string const& name) const;

        bool SetObjectName(std::string const& name, ObjectID id);

        void SortObjectsForRendering() const;

        GameObject& CreateGameObject();
        GameObject& CreateGameObject(std::string const& name);

        template<typename EventArgType, typename... Args> requires DerivedEventArg<EventArgType>
        void SendEventToAllObjects(Args&& ... args);

        bool UnsetGameObjectName(ObjectID id);

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
        mutable std::vector<GameObject const*> m_SortedRenderObjects{};
    };

    template<typename EventArgType, typename ...Args> requires DerivedEventArg<EventArgType>
    inline void Scene::SendEventToAllObjects(Args && ...args)
    {
        for (auto& object : m_Objects)
        {
            object->SendEvent<EventArgType>(std::forward<Args>(args)...);
        }
    }

}  // namespace dae

#endif