#include "AssetManager/SoundManager.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace he
{
    SoundManager::~SoundManager()
    {
        for (auto it = _assets.begin(); it != _assets.end(); ++it)
        {
            _assets[it->first] = nullptr;
        }
    }

    void SoundManager::Load(const std::string& id, const std::string& filepath)
    {
        LOG(INFO) << "Attempting to load sound '" << filepath << "' as id '" << id << "'\n";
        std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();
        if (soundBuffer->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(soundBuffer);
            LOG(INFO) << "Loaded sound '" << filepath << "' as id '" << id << "'\n";
        }
        else
        {
            LOG(WARNING) << "Failed to load sound '" << filepath << "'\n";
            soundBuffer->loadFromMemory(he::res::VINE_BOOM_ONE, he::res::VINE_BOOM_ONE_SIZE);
            this->_assets[id] = std::move(soundBuffer);
        }
    }

    void SoundManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            LOG(INFO) << "Unloaded sound of id '" << id << "'\n";
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
