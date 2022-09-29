#include "AssetManager/MusicManager.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Audio.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void MusicManager::Load(const std::string& filepath)
    {
    }
    /*void MusicManager::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::critical("[engine] MusicManager::Load(): Attempting to load music '{0}' as id '{1}'", filepath, id);
        std::unique_ptr<sf::Music> music = std::unique_ptr<sf::Music>(new sf::Music());
        if (music->openFromFile(filepath))
        {
            this->_assets[id] = std::move(music);
        }
        else
        {
            spdlog::critical("[engine] MusicManager::Load(): Failed to load music '{0}'", filepath);
            music->openFromMemory(he::res::VINE_BOOM_ONE, he::res::VINE_BOOM_ONE_SIZE);
            this->_assets[id] = std::move(music);
        }
    }

    void MusicManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::critical("[engine] MusicManager::Unload(): Unloaded music of id '{0}'", id);
        }
    }

    sf::Music& MusicManager::Get(const std::string& id)
    {
        return *(this->_assets.at(id));
    }

    const sf::Music& MusicManager::Get(const std::string& id) const
    {
        return *(this->_assets.at(id));
    }*/
} // namespace he
