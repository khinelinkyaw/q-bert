#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include <Engine/Misc/Singleton.h>
#include <Engine/Audio/SoundSystem.h>
#include <Engine/Physics/CollisionSystem.h>

#include <memory>
#include <utility>

namespace GameEngine
{
    class ServiceLocator final : public Singleton<ServiceLocator>
    {
    private:
        std::unique_ptr<SoundSystem> m_SoundSystem{ std::make_unique<NullSoundSystem>() };
        std::unique_ptr<CollisionSystem> m_CollisionSystem{ std::make_unique<CollisionSystem>() };

        friend class Singleton<ServiceLocator>;
        ServiceLocator() = default;

    public:
        SoundSystem& GetSoundSystem() { return *m_SoundSystem; }
        CollisionSystem& GetCollisionSystem() { return *m_CollisionSystem; }
        void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) { m_SoundSystem = std::move(soundSystem); }
    };
}

#endif