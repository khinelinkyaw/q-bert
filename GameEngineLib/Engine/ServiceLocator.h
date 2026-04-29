#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include <Engine/Misc/Singleton.h>

#include <memory>
#include <utility>

namespace GameEngine
{
    class SoundSystem;
    class ServiceLocator final : public Singleton<ServiceLocator>
    {
    private:
        std::unique_ptr<SoundSystem> m_SoundSystem{};

        friend class Singleton<ServiceLocator>;
        ServiceLocator() = default;

    public:
        SoundSystem& GetSoundSystem() { return *m_SoundSystem; }
        void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) { m_SoundSystem = std::move(soundSystem); }
    };
}

#endif
