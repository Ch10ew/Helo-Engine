#include "AssetManager/TextureManager.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void TextureManager::Load(const std::string& id, const std::string& filepath)
    {
        LOG(INFO) << "Attempting to load texture '" << filepath << "' as id '" << id << "'\n";
        std::unique_ptr<sf::Texture> texture = std::unique_ptr<sf::Texture>(new sf::Texture());
        if (texture->loadFromFile(filepath))
        {
            this->_assets[id] = std::move(texture);
            LOG(INFO) << "Loaded texture '" << filepath << "' as id '" << id << "'\n";
        }
        else
        {
            LOG(WARNING) << "Failed to load texture '" << filepath << "'\n";
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
            LOG(INFO) << "Unloaded texture of id '" << id << "'\n";
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
