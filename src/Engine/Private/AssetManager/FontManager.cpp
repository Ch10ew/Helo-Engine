#include "AssetManager/FontManager.hpp"

#include "FallbackResources/ArialBlack.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void FontManager::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::info("[engine] FontManager::Load(): Attempting to load font '{0}' as id '{1}'", filepath, id);
        std::unique_ptr<sf::Font> font = std::unique_ptr<sf::Font>(new sf::Font());
        if (font->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(font);
            spdlog::info("[engine] FontManager::Load(): Loaded font '{0}' as id '{1}'", filepath, id);
        }
        else
        {
            spdlog::critical("[engine] FontManager::Load(): Failed to load font '{0}'", filepath);
            font->loadFromMemory(he::res::FONT_ARIAL_BLACK, he::res::FONT_ARIAL_BLACK_SIZE);
            this->_assets[id] = std::move(font);
        }
    }

    void FontManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::info("[engine] FontManager::Unload(): Unloaded font of id '{0}'", id);
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
