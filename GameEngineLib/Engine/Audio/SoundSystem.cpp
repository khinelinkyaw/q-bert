#include "SoundSystem.h"

#include <Engine/macros.h>

#include <miniaudio.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

class MiniAudioSoundSystem::AudioImpl final
{
private:
    ma_engine m_Engine{};
    std::unordered_map<int, ma_sound> m_SoundMap;
    std::queue<int> m_PlayQueue;
    ma_engine_config m_EngineConfig{};
    std::mutex queueMutex{};
    std::mutex fileLoadingMutex{};
    std::condition_variable cv{};
    std::jthread consumer{};

    void ConsumeQueue();
    void LoadSoundFile(int soundId, std::string const& filePath);

public:
    void Play(int soundId);
    void Load(int soundId, std::string const& filePath);
    AudioImpl();
    ~AudioImpl();
};

void MiniAudioSoundSystem::AudioImpl::ConsumeQueue()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this] { return !m_PlayQueue.empty(); });

        int soundId = m_PlayQueue.front();
        m_PlayQueue.pop();

        lock.unlock();

        DEBUG_CONSOLE("Playing " << soundId)

        auto iter{ m_SoundMap.find(soundId) };

        if (iter == m_SoundMap.end())
        {
            DEBUG_CONSOLE("Sound " << soundId << " not found")
            continue;
        }

        ma_sound_start(&(iter->second));
    }
}

void MiniAudioSoundSystem::AudioImpl::LoadSoundFile(int soundId, std::string const& filePath)
{
    std::lock_guard<std::mutex> lock(fileLoadingMutex);
    DEBUG_CONSOLE("Loading sound at " << filePath)

    auto findIter{ m_SoundMap.find(soundId) };

    if (findIter != m_SoundMap.end())
    {
        DEBUG_CONSOLE("Sound file with ID " << soundId << " already loaded")
        return;
    }

    auto [iter, condition] = m_SoundMap.insert({ soundId, ma_sound{} });

    auto result{ ma_sound_init_from_file(&m_Engine, filePath.c_str(), 0, nullptr, nullptr, &iter->second) };

    if (result != MA_SUCCESS)
    {
        DEBUG_CONSOLE("Sound file " << filePath << " could not be loaded")
    }
}

void MiniAudioSoundSystem::AudioImpl::Play(int soundId)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    m_PlayQueue.push(soundId);
    DEBUG_CONSOLE("Pushed " << soundId << " to the queue")
    cv.notify_one();
}

void MiniAudioSoundSystem::AudioImpl::Load(int soundId, std::string const& filePath)
{
    //auto result{ std::async(std::launch::async, [soundId, &filePath, this] { this->LoadSoundFile(soundId, filePath); }) };
    std::thread newThread([soundId, filePath, this]
        {
            this->LoadSoundFile(soundId, filePath);
        });

    newThread.detach();
}

MiniAudioSoundSystem::AudioImpl::AudioImpl()
{
    ma_result result{};
    ma_sound sound{};

    result = ma_engine_init(nullptr, &m_Engine);

    if (result != MA_SUCCESS)
    {
        DEBUG_CONSOLE("Engine initialization failed\n")
    }
    else
    {
        consumer = std::jthread([this] { this->ConsumeQueue(); });
    }
}

MiniAudioSoundSystem::AudioImpl::~AudioImpl()
{
    for (auto& [id, sound] : m_SoundMap)
    {
        ma_sound_uninit(&sound);
    }

    ma_engine_uninit(&m_Engine);
}

void MiniAudioSoundSystem::Play(int)
{
    m_Impl->Play(0);
}

void MiniAudioSoundSystem::Load(int soundId, std::string const& filePath)
{
    m_Impl->Load(soundId, filePath);
}


MiniAudioSoundSystem::MiniAudioSoundSystem()
    : m_Impl{ std::make_unique<AudioImpl>() }
{
}

MiniAudioSoundSystem::~MiniAudioSoundSystem() = default;
