#ifndef HE_MUSIC_PLAYER_HPP
#define HE_MUSIC_PLAYER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Audio.hpp>

namespace he
{
    class MusicPlayer
    {
    public:
        void Load(const std::string& id, const std::string& filepath);
        void Unload(const std::string& id);
        sf::Music& Get(const std::string& id);
        const sf::Music& Get(const std::string& id) const;
        const std::string& GetMusic(const std::string& id) const;
        sf::SoundSource::Status GetStatus() const;

    private:
        std::map<std::string, std::string> _musicpaths;
        sf::Music _music;
        float _volume;
    };
} // namespace he

#endif // HE_MUSIC_PLAYER_HPP
