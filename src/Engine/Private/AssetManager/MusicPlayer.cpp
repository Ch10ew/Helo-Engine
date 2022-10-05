#include "AssetManager/MusicPlayer.hpp"

#include "FallbackResources/VineBoomOne.hpp"

#include <SFML/Audio.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void MusicPlayer::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::info("[engine] MusicPlayer::Load(): Registering music '{0}' as id '{1}'", filepath, id);
        this->_musicSources[id] = filepath;
        spdlog::info("[engine] MusicPlayer::Load(): Registered music '{0}' as id '{1}'", filepath, id);
    }

    void MusicPlayer::Unload(const std::string& id)
    {
        if (_musicSources.find(id) != _musicSources.end())
        {
            _musicSources.erase(_musicSources.find(id));
            spdlog::info("[engine] MusicPlayer::Unload(): Unregistered music of id '{0}'", id);
        }
    }

    void MusicPlayer::Use(const std::string& id)
    {
        if (_music.openFromFile(_musicSources[id]))
        {
            spdlog::info("[engine] MusicPlayer::Use(): Loaded music into Music instance '{0}'", _musicSources[id]);
        }
        else
        {
            spdlog::critical("[engine] MusicPlayer::Use(): Failed to load music into Music instance '{0}'", _musicSources[id]);
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
