#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <memory>
#include <string>

class SoundSystem
{
public:
    virtual void Play(int soundId) = 0;
    virtual void Load(int soundId, std::string const& filePath) = 0;

    virtual ~SoundSystem() = default;
};

class MiniAudioSoundSystem final: public SoundSystem
{
private:
    class AudioImpl;
    std::unique_ptr<AudioImpl> m_Impl{};

public:
    void Play(int soundId);
    void Load(int soundId, std::string const& filePath) override;

    MiniAudioSoundSystem();
    ~MiniAudioSoundSystem();
};

#endif
