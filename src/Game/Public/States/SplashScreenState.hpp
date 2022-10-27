#ifndef TTT_SPLASH_SCREEN_STATE_HPP
#define TTT_SPLASH_SCREEN_STATE_HPP

#include "AssetManager/Assets.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/GameState.hpp"

#include <SFML/Graphics.hpp>

namespace ttt
{
    class SplashScreenState : public he::GameState
    {
    public:
        SplashScreenState();

    public:
        void ProcessInput(sf::Event event);
        void Update(float dt);
        void Render(float dt);

    public:
        void Init();
        void Pause();
        void Resume();

    private:
        he::CoreGameData* _coreGameData;
        he::Assets* _assets;

    private:
        const int SPLASH_TIME = 3000;

    private:
        sf::CircleShape _circleShape;
        sf::Sprite _test;

    private:
        sf::Clock _clock;
    };
} // namespace ttt

#endif // TTT_SPLASH_SCREEN_STATE_HPP
