#include "AssetManager/ShaderManager.hpp"

#include "FallbackResources/SwirlShader.hpp"

#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void ShaderManager::Load(const std::string& id, const std::string& filepath, sf::Shader::Type type)
    {
        spdlog::info("[engine] ShaderManager::Load(): Attempting to load shader '{0}' as id '{1}'", filepath, id);
        std::unique_ptr<sf::Shader> shader;
        if (shader->loadFromFile(filepath, type))
        {
            this->_assets[id] = std::move(shader);
            spdlog::info("[engine] ShaderManager::Load(): Loaded shader '{0}' as id '{1}'", filepath, id);
        }
        else
        {
            spdlog::critical("[engine] ShaderManager::Load(): Failed to load shader '{0}'", filepath);
            shader->loadFromMemory(he::res::SWIRL_SHADER_STRING, sf::Shader::Type::Vertex);
            this->_assets[id] = std::move(shader);
        }
    }

    void ShaderManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            spdlog::info("[engine] ShaderManager::Unload(): Unloaded shader of id '{0}'", id);
        }
    }

    sf::Shader& ShaderManager::Get(const std::string& id)
    {
        return *(this->_assets.at(id));
    }

    const sf::Shader& ShaderManager::Get(const std::string& id) const
    {
        return *(this->_assets.at(id));
    }
} // namespace he
