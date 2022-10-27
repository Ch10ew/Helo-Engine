#ifndef HE_TEXTURE_MANAGER_HPP
#define HE_TEXTURE_MANAGER_HPP

#include "AssetManager/AssetManagerBase.hpp"

#include <string>

#include <SFML/Graphics.hpp>

namespace he
{
    /**
     * Texture collection for the game. Textures are persistent throughout the lifetime of the program.
     *
     * IDs are local to the texture collection and are not shared with other collections.
     */
    class TextureManager : public AssetManagerBase<sf::Texture>
    {
    public:
        /**
         * Loads a texture from `filepath`, with id of `id`.
         *
         * @param id Unique identifier for the texture.
         * @param filepath Filepath to texture.
         */
        void Load(const std::string& id, const std::string& filepath);

        /**
         * Unloads a texture with id of `id`.
         *
         * @param id Unique identifier for the texture.
         */
        void Unload(const std::string& id);
        sf::Texture& Get(const std::string& id);
        const sf::Texture& Get(const std::string& id) const;
    };
} // namespace he

#endif // HE_TEXTURE_MANAGER_HPP
