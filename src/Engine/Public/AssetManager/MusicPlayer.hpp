#ifndef HE_MUSIC_PLAYER_HPP
#define HE_MUSIC_PLAYER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Audio.hpp>

namespace he
{
    /**
     * @brief Music Player to play BGMs.
     */
    class MusicPlayer
    {
    public:
        void Load(const std::string& id, const std::string& filepath);
        void Unload(const std::string& id);
        void Use(const std::string& id);
        sf::Music& Get();
        const sf::Music& Get() const;

    private:
        std::map<std::string, std::string> _musicSources;
        sf::Music _music;
    };
} // namespace he

#endif // HE_MUSIC_PLAYER_HPP
