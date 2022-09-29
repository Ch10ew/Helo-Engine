/*#include "AssetManager/SoundManager.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <sstream>
#include <string>

namespace he
{
    void SoundManager::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::critical("[engine] SoundManager::Load(): Attempting to load sound '{0}' as id '{1}'", filepath, id);
        sf::SoundBuffer soundBuffer;
        if (soundBuffer.loadFromFile(filepath))
        {
            this->_assets[id] = soundBuffer;
        }
        else
        {
            spdlog::critical("[engine] SoundManager::Load(): Failed to load sound '{0}'", filepath);
            soundBuffer.loadFromMemory(he::res::VINE_BOOM_ONE, he::res::VINE_BOOM_ONE_SIZE);
            this->_assets[id] = soundBuffer;
        }
    }

    void SoundManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::critical("[engine] SoundManager::Unload(): Unloaded sound of id '{0}'", id);
        }
    }

    sf::SoundBuffer& SoundManager::Get(const std::string& id)
    {
        return this->_assets.at(id);
    }
} // namespace he
*/