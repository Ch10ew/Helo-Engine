#include "AssetManager/FontManager.hpp"

#include "FallbackResources/ArialBlack.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void FontManager::Load(const std::string& id, const std::string& filepath)
    {
        LOG(INFO) << "Attempting to load font '" << filepath << "' as id '" << id << "'\n";
        std::unique_ptr<sf::Font> font = std::unique_ptr<sf::Font>(new sf::Font());
        if (font->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(font);
            LOG(INFO) << "Loaded font '" << filepath << "' as id '" << id << "'\n";
        }
        else
        {
            LOG(WARNING) << "Failed to load font '" << filepath << "'\n";
            font->loadFromMemory(he::res::FONT_ARIAL_BLACK, he::res::FONT_ARIAL_BLACK_SIZE);
            this->_assets[id] = std::move(font);
        }
    }

    void FontManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            LOG(INFO) << "Unloaded font of id '" << id << "'\n";
        }
    }

    sf::Font& FontManager::Get(const std::string& id)
    {
        return *(this->_assets.at(id));
    }

    const sf::Font& FontManager::Get(const std::string& id) const
    {
        return *(this->_assets.at(id));
    }
} // namespace he
