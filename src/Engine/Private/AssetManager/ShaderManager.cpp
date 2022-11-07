#include "AssetManager/ShaderManager.hpp"

#include "FallbackResources/SwirlShader.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

#include <iostream>
#include <memory>
#include <string>

namespace he
{
    void ShaderManager::Load(const std::string& id, const std::string& filepath, sf::Shader::Type type)
    {
        LOG(INFO) << "Attempting to load shader '" << filepath << "' as id '" << id << "'\n";
        std::unique_ptr<sf::Shader> shader;
        if (shader->loadFromFile(filepath, type))
        {
            this->_assets[id] = std::move(shader);
            LOG(INFO) << "Loaded shader '" << filepath << "' as id '" << id << "'\n";
        }
        else
        {
            LOG(WARNING) << "Failed to load shader '" << filepath << "'\n";
            shader->loadFromMemory(he::res::SWIRL_SHADER_STRING, sf::Shader::Type::Vertex);
            this->_assets[id] = std::move(shader);
        }
    }

    void ShaderManager::Unload(const std::string& id)
    {
        if (_assets.find(id) != _assets.end())
        {
            _assets.erase(_assets.find(id));
            LOG(INFO) << "Unloaded shader of id '" << id << "'\n";
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
