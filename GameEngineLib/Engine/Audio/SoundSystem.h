#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <memory>
#include <string>

namespace GameEngine
{
    class SoundSystem
    {
    public:
        virtual void SetMute(bool isMuted) = 0;
        virtual void Play(int soundId) = 0;
        virtual void Load(int soundId, std::string const& filePath) = 0;

        virtual ~SoundSystem() = default;
    };

    class NullSoundSystem final : public SoundSystem
    {
    public:
        void SetMute(bool) override {};
        void Play(int) override {};
        void Load(int, std::string const&) override {};

        ~NullSoundSystem() override = default;
    };

    class MiniAudioSoundSystem final : public SoundSystem
    {
    private:
        class AudioImpl;
        std::unique_ptr<AudioImpl> m_Impl{};
        bool m_IsMuted{ false };

    public:
        void SetMute(bool isMuted) override;
        void Play(int soundId) override;
        void Load(int soundId, std::string const& filePath) override;

        MiniAudioSoundSystem();
        ~MiniAudioSoundSystem() override;
    };
}

#endif
