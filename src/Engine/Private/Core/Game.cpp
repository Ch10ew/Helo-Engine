#include "Core/Game.hpp"

#include "Core/CoreGameData.hpp"

#include <aixlog.hpp>

#include <memory>
#include <string>

namespace he
{
    Game::Game()
        : _coreGameData(CoreGameData::GetInstance())
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData.window.create(sf::VideoMode(800, 600), "title");
        _coreGameData.window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData.window.getDefaultView();
    }

    Game::Game(std::string title)
        : _coreGameData(CoreGameData::GetInstance())
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData.window.create(sf::VideoMode(800, 600), title);
        _coreGameData.window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData.window.getDefaultView();
    }

    Game::Game(int width, int height, std::string title)
        : _coreGameData(CoreGameData::GetInstance())
    {
        AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace); // Init logger

        _coreGameData.window.create(sf::VideoMode(width, height), title);
        _coreGameData.window.setFramerateLimit(_framerateLimit);

        _view = _coreGameData.window.getDefaultView();
    }

    void Game::SetInitialState(std::unique_ptr<GameState> state)
    {
        LOG(INFO) << "Setting initial state...\n";
        _coreGameData.stateMachine.AddState(std::move(state), false);
    }

    void Game::Run()
    {
        LOG(INFO) << "Main game loop starting...\n";
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (_coreGameData.window.isOpen())
        {
            // State changes
            _coreGameData.stateMachine.ProcessStateChanges();

#pragma region Handle Input

            _coreGameData.eventPolledCurrentFrame = false;
            _coreGameData.events.clear();
            sf::Event event;
            while (_coreGameData.window.pollEvent(event))
            {
                _coreGameData.eventPolledCurrentFrame = true;
                _coreGameData.events.push_back(event);

                if (event.type == sf::Event::Resized)
                {
                    _view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height)); // Resizing based on 0, 0
                    //_view.setSize(sf::Vector2f(event.size.width, event.size.height)); // Resizing based on initial center
                }

                if (event.type == sf::Event::Closed)
                {
                    _coreGameData.window.close();
                }
            }

#pragma endregion

#pragma region Clear

            _coreGameData.window.clear(sf::Color::White);

#pragma endregion

#pragma region Update

            _coreGameData.stateMachine.GetActiveState()->GameState::Update(_timestep); // Base class update
            _coreGameData.stateMachine.GetActiveState()->Update(_timestep);            // Derived class update
            _coreGameData.window.setView(_view);

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

                _coreGameData.stateMachine.GetActiveState()->GameState::FixedUpdate(_timestep);
                _coreGameData.stateMachine.GetActiveState()->FixedUpdate(_timestep);

#pragma endregion

                accumulator -= _timestep;
            }

#pragma region Display

            _coreGameData.window.display();

#pragma endregion
        }
    }
} // namespace he
