#include "Core/Game.hpp"

#include "Core/CoreGameData.hpp"
#include "States/SplashScreenState.hpp"

#include <aixlog.hpp>

#include <memory>
#include <string>

namespace he
{
    Game::Game()
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(800, 600), "title");
        _coreGameData->window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData->window.getDefaultView();
    }

    Game::Game(std::string title)
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(800, 600), title);
        _coreGameData->window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData->window.getDefaultView();
    }

    Game::Game(int width, int height, std::string title)
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData = CoreGameData::GetInstance();
        _coreGameData->window.create(sf::VideoMode(width, height), title);
        _coreGameData->window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData->window.getDefaultView();
    }

    void Game::SetInitialState(std::unique_ptr<GameState> state)
    {
        LOG(INFO) << "Setting initial state...\n";
        _coreGameData->stateMachine.AddState(std::move(state), false);
    }

    void Game::Run()
    {
        LOG(INFO) << "Main game loop starting...\n";
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (_coreGameData->window.isOpen())
        {
            // State changes
            _coreGameData->stateMachine.ProcessStateChanges();

#pragma region Input

            sf::Event event;
            while (_coreGameData->window.pollEvent(event))
            {
                if (event.type == sf::Event::Resized)
                {
                    _view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height)); // Resizing based on 0, 0
                    //_view.setSize(sf::Vector2f(event.size.width, event.size.height)); // Resizing based on initial center
                }

                if (event.type == sf::Event::Closed)
                {
                    _coreGameData->window.close();
                }

                _coreGameData->stateMachine.GetActiveState()->ProcessInput(event);
            }

#pragma endregion

#pragma region Update

            _coreGameData->stateMachine.GetActiveState()->Update(_timestep);
            _coreGameData->window.setView(_view);

#pragma endregion

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

#pragma region Physics Update

                _coreGameData->stateMachine.GetActiveState()->FixedUpdate(_timestep);

#pragma endregion

                accumulator -= _timestep;
            }

#pragma region Display

            _coreGameData->stateMachine.GetActiveState()->Render();

#pragma endregion
        }
    }
} // namespace he
