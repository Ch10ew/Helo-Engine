#ifndef SPLASH_SCREEN_STATE_HPP
#define SPLASH_SCREEN_STATE_HPP

#include "Core/CoreGameData.hpp"
#include "Core/GameState.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    class SplashScreenState : public GameState
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
        CoreGameData* _coreGameData;

        sf::Clock _clock;

        const int SPLASH_TIME = 3000;

        sf::CircleShape _circleShape;
    };
} // namespace he

#endif // SPLASH_SCREEN_STATE_HPP
