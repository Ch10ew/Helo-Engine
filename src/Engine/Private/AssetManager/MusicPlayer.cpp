#include "AssetManager/MusicPlayer.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Audio.hpp>
#include <aixlog.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void MusicPlayer::Load(const std::string& id, const std::string& filepath)
    {
        LOG(INFO) << "Registering music '" << filepath << "' as id '" << id << "'\n";
        this->_musicSources[id] = filepath;
        LOG(INFO) << "Registered music '" << filepath << "' as id '" << id << "'\n";
    }

    void MusicPlayer::Unload(const std::string& id)
    {
        if (_musicSources.find(id) != _musicSources.end())
        {
            _musicSources.erase(_musicSources.find(id));
            LOG(INFO) << "Unregistered music of id '" << id << "'\n";
        }
    }

    void MusicPlayer::Use(const std::string& id)
    {
        if (_music.openFromFile(_musicSources[id]))
        {
            LOG(INFO) << "Loaded music into Music instance '" << _musicSources[id] << "'\n";
        }
        else
        {
            LOG(WARNING) << "Failed to load music into Music instance '" << _musicSources[id] << "'\n";
            _music.openFromMemory(he::res::VINE_BOOM_ONE, he::res::VINE_BOOM_ONE_SIZE);
        }
    }

    sf::Music& MusicPlayer::Get()
    {
        return _music;
    }

    const sf::Music& MusicPlayer::Get() const
    {
        return _music;
    }
} // namespace he
