#include "Core/Game.hpp"
#include "Core/CoreGameData.hpp"
#include "TicTacToe/SplashScreenState.hpp"

#include <memory>
#include <string>

namespace he
{
    Game::Game()
    {
        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(800, 600), "title");
        _coreGameData->window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData->window.getDefaultView();
    }

    Game::Game(std::string title)
    {
        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(800, 600), title);
        _coreGameData->window.setFramerateLimit(_framerateLimit);
    }

    Game::Game(int width, int height, std::string title)
    {
        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(width, height), title);
        _coreGameData->window.setFramerateLimit(_framerateLimit);
    }

    void Game::SetInitialState(std::unique_ptr<GameState> state)
    {
        _coreGameData->stateMachine.AddState(std::move(state));
    }

    void Game::Run()
    {
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (_coreGameData->window.isOpen())
        {
            // State changes
            _coreGameData->stateMachine.ProcessStateChanges();

            float newTime = this->_clock.getElapsedTime().asSeconds();
            float frameTime = newTime - currentTime;
            if (frameTime > 0.25f)
            {
                frameTime = 0.25f;
            }
            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= _timestep)
            {

#pragma region State changes

                _coreGameData->stateMachine.ProcessStateChanges();

#pragma endregion

#pragma region Input

                sf::Event event;
                while (_coreGameData->window.pollEvent(event))
                {
                    if (event.type == sf::Event::Resized)
                    {
                        _view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height)); // Resizing based on 0, 0
                        //_view.setSize(sf::Vector2f(event.size.width, event.size.height)); // Resizing based on initial center
                    }

                    _coreGameData->stateMachine.GetActiveState()->ProcessInput(event);
                }

#pragma endregion

#pragma region Update

                _coreGameData->window.setView(_view);
                _coreGameData->stateMachine.GetActiveState()->Update(_timestep);

#pragma endregion

                accumulator -= _timestep;
            }

            // [0, 1] | How much to interpolate from previous state to get to the current state
            const float interpolation = accumulator / _timestep;

#pragma region Display

            _coreGameData->stateMachine.GetActiveState()->Render(_timestep);

#pragma endregion
        }
    }
} // namespace he
