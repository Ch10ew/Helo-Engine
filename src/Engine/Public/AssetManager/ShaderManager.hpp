/*#ifndef HE_SHADER_MANAGER_HPP
#define HE_SHADER_MANAGER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Graphics.hpp>

namespace he
{
    class ShaderManager : public AssetManagerBase<sf::Shader>
    {
    public:
        void Load(const std::string& id, const std::string& filepath, sf::Shader::Type type);
        void Unload(const std::string& id);
        sf::Shader& Get(const std::string& id);
    };
} // namespace he

#endif // HE_SHADER_MANAGER_HPP
*/