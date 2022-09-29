#ifndef HE_FONT_MANAGER_HPP
#define HE_FONT_MANAGER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Graphics.hpp>

namespace he
{
    class FontManager : public AssetManagerBase<sf::Font>
    {
    public:
        void Load(const std::string& id, const std::string& filepath);
        void Unload(const std::string& id);
        sf::Font& Get(const std::string& id);
        const sf::Font& Get(const std::string& id) const;
    };
} // namespace he

#endif // HE_FONT_MANAGER_HPP
