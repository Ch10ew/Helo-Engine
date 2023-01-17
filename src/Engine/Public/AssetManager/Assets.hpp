#ifndef HE_ASSETS_HPP
#define HE_ASSETS_HPP

#include "AssetManager/FontManager.hpp"
#include "AssetManager/MusicPlayer.hpp"
#include "AssetManager/ShaderManager.hpp"
#include "AssetManager/SoundManager.hpp"
#include "AssetManager/TextureManager.hpp"

namespace he
{
    class Assets
    {
    private:
        /**
         * Construct a new Assets object. Private to block new instances from being created.
         */
        Assets();

        /**
         * Destroy the Assets object.
         */
        ~Assets();

    public:
        /**
         * Disabled Copy Constructor
         */
        Assets(Assets& other) = delete;

        /**
         * Disabled assignment operator
         */
        void operator=(const Assets& other) = delete;

        /**
         * Gets the instance of this singleton.
         */
        static Assets& GetInstance();

    public:
        /**
         * Font collection of the game.
         */
        FontManager fontManager;

        /**
         * Shader collection of the game.
         */
        ShaderManager shaderManager;

        /**
         * Sound collection of the game.
         */
        SoundManager soundManager;

        /**
         * Texture collection of the game.
         */
        TextureManager textureManager;

        /**
         * Music collection of the game.
         */
        MusicPlayer musicPlayer;
    };
} // namespace he

#endif // HE_ASSETS_HPP
