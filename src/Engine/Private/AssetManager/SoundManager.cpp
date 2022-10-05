#include "AssetManager/SoundManager.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace he
{
    void SoundManager::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::info("[engine] SoundManager::Load(): Attempting to load sound '{0}' as id '{1}'", filepath, id);
        std::unique_ptr<sf::SoundBuffer> soundBuffer;
        if (soundBuffer->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(soundBuffer);
            spdlog::info("[engine] SoundManager::Load(): Loaded sound '{0}' as id '{1}'", filepath, id);
        }
        else
        {
            spdlog::critical("[engine] SoundManager::Load(): Failed to load sound '{0}'", filepath);
            soundBuffer->loadFromMemory(he::res::VINE_BOOM_ONE, he::res::VINE_BOOM_ONE_SIZE);
            this->_assets[id] = std::move(soundBuffer);
        }
    }

    void SoundManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::info("[engine] SoundManager::Unload(): Unloaded sound of id '{0}'", id);
        }
    }

    sf::SoundBuffer& SoundManager::Get(const std::string& id)
    {
        return *(this->_assets.at(id));
    }

    const sf::SoundBuffer& SoundManager::Get(const std::string& id) const
    {
        return *(this->_assets.at(id));
    }
} // namespace he
