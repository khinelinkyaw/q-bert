#include <Engine/Audio/SoundSystem.h>
#include <Engine/Core/Macros.h>
#include <Engine/Core/ResourceManager.h>

#include <miniaudio.h>

#include <memory>
#include <queue>

#ifndef __EMSCRIPTEN__
    #include <condition_variable>
    #include <mutex>
    #include <stop_token>
    #include <thread>
#endif

#include <string>
#include <unordered_map>
#include <utility>

using namespace GameEngine;

class MiniAudioSoundSystem::AudioImpl final
{
private:
    ma_engine m_Engine{};
    std::unordered_map<int, ma_sound> m_SoundMap;
    std::queue<int> m_PlayQueue;

#ifndef __EMSCRIPTEN__
    std::mutex queueMutex{};
    std::mutex fileLoadingMutex{};
    std::condition_variable cv{};
    std::jthread consumer{};

    void ConsumeQueue(std::stop_token stopToken);
#else
    void ConsumeQueue();
#endif
    void LoadSoundFile(int soundId, std::string const& filePath);

public:
    void Play(int soundId);
    void Load(int soundId, std::string const& filePath);
    AudioImpl();
    ~AudioImpl();
};

#ifndef __EMSCRIPTEN__
void MiniAudioSoundSystem::AudioImpl::ConsumeQueue(std::stop_token stopToken)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        cv.wait(lock, [this, &stopToken] { return !m_PlayQueue.empty() or stopToken.stop_requested(); });
        if (stopToken.stop_requested()) return;

        int soundId = m_PlayQueue.front();
        m_PlayQueue.pop();

        lock.unlock();

        //DEBUG_CONSOLE("SoundSystem", "Playing " << soundId)

        auto iter{ m_SoundMap.find(soundId) };

        if (iter == m_SoundMap.end())
        {
            DEBUG_CONSOLE("SoundSystem", "Sound " << soundId << " not found")
                continue;
        }

        ma_sound_start(&(iter->second));
    }
}
#else
void MiniAudioSoundSystem::AudioImpl::ConsumeQueue()
{
    while (true)
    {
        int soundId = m_PlayQueue.front();
        m_PlayQueue.pop();

        auto iter{ m_SoundMap.find(soundId) };

        if (iter == m_SoundMap.end())
        {
            DEBUG_CONSOLE("SoundSystem", "Sound " << soundId << " not found")
                continue;
        }

        ma_sound_start(&(iter->second));
    }
}
#endif


void MiniAudioSoundSystem::AudioImpl::LoadSoundFile(int soundId, std::string const& filePath)
{
#ifndef __EMSCRIPTEN__
    std::lock_guard<std::mutex> lock(fileLoadingMutex);
#endif
    DEBUG_CONSOLE("SoundSystem","Loading sound at " << filePath)

    auto findIter{ m_SoundMap.find(soundId) };

    if (findIter != m_SoundMap.end())
    {
        DEBUG_CONSOLE("SoundSystem","Sound file with ID " << soundId << " already loaded")
        return;
    }

    auto [iter, condition] = m_SoundMap.insert({ soundId, ma_sound{} });

    auto soundFilePath{ GameEngine::ResourceManager::Get().GetDataFilePath(filePath) };

    auto result{ ma_sound_init_from_file(&m_Engine, soundFilePath.string().c_str(), 0, nullptr, nullptr, &iter->second)};

    if (result != MA_SUCCESS)
    {
        DEBUG_CONSOLE("SoundSystem","Sound file " << filePath << " could not be loaded")
    }
}

void MiniAudioSoundSystem::AudioImpl::Play(int soundId)
{
#ifndef __EMSCRIPTEN__
    std::lock_guard<std::mutex> lock(queueMutex);
    m_PlayQueue.push(soundId);
    cv.notify_one();
#else
    m_PlayQueue.push(soundId);
    ConsumeQueue();
#endif
}

void MiniAudioSoundSystem::AudioImpl::Load(int soundId, std::string const& filePath)
{
#ifndef __EMSCRIPTEN__
    std::jthread newThread([soundId, filePath, this]
        {
            this->LoadSoundFile(soundId, filePath);
        });

    newThread.detach();
#else
    LoadSoundFile(soundId, filePath);
#endif
}

MiniAudioSoundSystem::AudioImpl::AudioImpl()
{
    ma_result result{};

    result = ma_engine_init(nullptr, &m_Engine);

    if (result != MA_SUCCESS)
    {
        DEBUG_CONSOLE("SoundSystem","Engine initialization failed\n")
    }
#ifndef __EMSCRIPTEN__
    else
    {
        consumer = std::jthread([this](std::stop_token stopToken) { this->ConsumeQueue(stopToken); });
    }
#endif
}

MiniAudioSoundSystem::AudioImpl::~AudioImpl()
{
#ifndef __EMSCRIPTEN__
    consumer.request_stop();
    cv.notify_one();
#endif

    for (auto& [id, sound] : m_SoundMap)
    {
        ma_sound_uninit(&sound);
    }

    ma_engine_uninit(&m_Engine);
}

void MiniAudioSoundSystem::Play(int soundId)
{
    m_Impl->Play(soundId);
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
