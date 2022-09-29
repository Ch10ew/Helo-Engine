#include "TicTacToe/SplashScreenState.hpp"
#include "Core/CoreGameData.hpp"

#include <iostream>

namespace ttt
{
    SplashScreenState::SplashScreenState()
    {
        _coreGameData = he::CoreGameData::GetInstance();
    }

    void SplashScreenState::ProcessInput(sf::Event event)
    {
        if (event.type == sf::Event::Closed)
        {
            _coreGameData->window.close();
        }
    }

    void SplashScreenState::Update(float dt)
    {
        if (_clock.getElapsedTime().asMilliseconds() > SPLASH_TIME)
        {
            //_coreGameData->stateMachine.AddState();
            // std::cout << "Done" << std::endl;
            _circleShape.setFillColor(sf::Color::Blue);
        }
    }

    void SplashScreenState::Render(float dt)
    {
        _coreGameData->window.clear(sf::Color::White);
        _coreGameData->window.draw(_circleShape);
        _coreGameData->window.display();
    }

    void SplashScreenState::Init()
    {
        _circleShape.setRadius(30);
        _circleShape.setFillColor(sf::Color::Green);
        _circleShape.setPosition(200, 200);
    }

    void SplashScreenState::Pause()
    {
    }

    void SplashScreenState::Resume()
    {
    }
} // namespace ttt
