#include <Engine/Core/Macros.h>
#include <Engine/Core/ResourceManager.h>
#include <Engine/Rendering/Font.h>
#include <Engine/Rendering/Texture2D.h>

#include <SDL3/SDL_error.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <utility>

namespace fs = std::filesystem;

using namespace GameEngine;

void ResourceManager::Init(const std::filesystem::path& dataPath)
{
    m_dataPath = dataPath;

    if (!TTF_Init())
    {
        throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
    }
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
    const auto fullPath = m_dataPath / file;
    const auto filename = fs::path(fullPath).filename().string();
    if (m_loadedTextures.find(filename) == m_loadedTextures.end())
    {
        try
        {
            m_loadedTextures.insert(std::pair(filename, std::make_shared<Texture2D>(fullPath.string())));
        }
        catch (std::runtime_error const&)
        {
            return nullptr;
        }
    }

    return m_loadedTextures.at(filename);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, uint8_t size)
{
    const auto fullPath = m_dataPath / file;
    const auto filename = fs::path(fullPath).filename().string();
    const auto key = std::pair<std::string, uint8_t>(filename, size);
    if (m_loadedFonts.find(key) == m_loadedFonts.end())
        m_loadedFonts.insert(std::pair(key, std::make_shared<Font>(fullPath.string(), size)));
    return m_loadedFonts.at(key);
}

json GameEngine::ResourceManager::LoadJSON(const std::string& file)
{
    const auto fullPath = m_dataPath / file;
    const auto filename = fs::path(fullPath).filename().string();

    std::ifstream jsonFile{ fullPath };

    try
    {
        return json::parse(jsonFile);
    }
    catch (json::parse_error const&)
    {
        DEBUG_CONSOLE("JSON", "Parse error of file: " << filename)
            return json{};
    }
}

void ResourceManager::UnloadUnusedResources()
{
    for (auto it = m_loadedTextures.begin(); it != m_loadedTextures.end();)
    {
        if (it->second.use_count() == 1)
            it = m_loadedTextures.erase(it);
        else
            ++it;
    }

    for (auto it = m_loadedFonts.begin(); it != m_loadedFonts.end();)
    {
        if (it->second.use_count() == 1)
            it = m_loadedFonts.erase(it);
        else
            ++it;
    }
}
