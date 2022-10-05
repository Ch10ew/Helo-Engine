#ifndef HE_SOUND_MANAGER_HPP
#define HE_SOUND_MANAGER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Audio.hpp>

namespace he
{
    class SoundManager : public AssetManagerBase<sf::SoundBuffer>
    {
    public:
        void Load(const std::string& id, const std::string& filepath);
        void Unload(const std::string& id);
        sf::SoundBuffer& Get(const std::string& id);
        const sf::SoundBuffer& Get(const std::string& id) const;
    };
} // namespace he

#endif // HE_SOUND_MANAGER_HPP
