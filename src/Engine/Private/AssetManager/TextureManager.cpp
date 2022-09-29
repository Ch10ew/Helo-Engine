#include "AssetManager/TextureManager.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void TextureManager::Load(const std::string& id, const std::string& filepath)
    {
        spdlog::critical("[engine] TextureManager::Load(): Attempting to load texture '{0}' as id '{1}'", filepath, id);
        std::unique_ptr<sf::Texture> texture = std::unique_ptr<sf::Texture>(new sf::Texture());
        if (texture->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(texture);
        }
        else
        {
            spdlog::critical("[engine] TextureManager::Load(): Failed to load texture '{0}'", filepath);
            sf::Image missingTextureImage;
            missingTextureImage.create(40, 40, sf::Color::Magenta);

            texture->loadFromImage(missingTextureImage);
            this->_assets[id] = std::move(texture);
        }
    }

    void TextureManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::critical("[engine] TextureManager::Unload(): Unloaded texture of id '{0}'", id);
        }
    }

    sf::Texture& TextureManager::Get(const std::string& id)
    {
        return *(this->_assets.at(id));
    }

    const sf::Texture& TextureManager::Get(const std::string& id) const
    {
        return *(this->_assets.at(id));
    }
} // namespace he
