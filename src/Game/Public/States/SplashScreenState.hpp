#ifndef TTT_SPLASH_SCREEN_STATE_HPP
#define TTT_SPLASH_SCREEN_STATE_HPP

#include "AssetManager/Assets.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/GameState.hpp"

#include "Scripts/SpriteExpander.hpp"

#include <SFML/Graphics.hpp>

namespace ttt
{
    class SplashScreenState : public he::GameState
    {
    public:
        SplashScreenState();

    public:
        void Update(float dt);
        void FixedUpdate(float dt);

    public:
        void Init();

    private:
        he::CoreGameData* _coreGameData;
        he::Assets* _assets;

    private:
        const int SPLASH_TIME = 1000;

    private:
        std::shared_ptr<ttt::SpriteExpander> se;

    private:
        sf::Clock _clock;
    };
} // namespace ttt

#endif // TTT_SPLASH_SCREEN_STATE_HPP
