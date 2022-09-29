/*#include "AssetManager/ShaderManager.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

namespace he
{
    void ShaderManager::Load(const std::string& id, const std::string& filepath, sf::Shader::Type type)
    {
        spdlog::critical("[engine] SoundManager::Load(): Attempting to load shader '{0}' as id '{1}'", filepath, id);
        sf::Shader shader;
        if (shader.loadFromFile(filepath, type))
        {
            this->_assets[id] = shader;
        }
        else
        {
            spdlog::critical("[engine] ShaderManager::Load(): Failed to load shader '{0}'", filepath);
            sf::Image missingShaderImage;
            missingShaderImage.create(40, 40, sf::Color::Magenta);

            shader.loadFromImage(missingShaderImage);
            this->_assets[id] = shader;
        }
    }

    void ShaderManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::critical("[engine] SoundManager::Unload(): Unloaded shader of id '{0}'", id);
        }
    }

    sf::Shader& ShaderManager::Get(const std::string& id)
    {
        return this->_assets.at(id);
    }
} // namespace he
*/