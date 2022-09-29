#ifndef HE_TEXTURE_MANAGER_HPP
#define HE_TEXTURE_MANAGER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Graphics.hpp>

namespace he
{
    class TextureManager : public AssetManagerBase<sf::Texture>
    {
    public:
        void Load(const std::string& id, const std::string& filepath);
        void Unload(const std::string& id);
        sf::Texture& Get(const std::string& id);
        const sf::Texture& Get(const std::string& id) const;
    };
} // namespace he

#endif // HE_TEXTURE_MANAGER_HPP
