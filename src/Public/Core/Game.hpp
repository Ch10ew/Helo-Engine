#ifndef GAME_HPP
#define GAME_HPP

#include "Core/CoreGameData.hpp"
#include "Core/StateMachine.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace he
{
    /**
     * Game class representing the entire game. Contains the main game loop.
     */
    class Game
    {
    public:
        /**
         * Construct a new Game object
         */
        Game();

        /**
         * @brief Construct a new Game object
         *
         * @param title Window title.
         */
        Game(std::string title);

        /**
         * @brief Construct a new Game object
         *
         * @param width Window width.
         * @param height Window height.
         * @param title Window title.
         */
        Game(int width, int height, std::string title);

        void SetInitialState(std::unique_ptr<GameState> state);

        /**
         * Starts the game. Runs the main game loop.
         *
         * The main game loop consists of 4 main operations:
         * - Process State Changes
         * - Process Inputs
         * - Update
         * - Draw
         *
         * The Process State Changes operation is called from the state machine (See StateMachine).
         *
         * The Process Inputs, Update, and Draw operations are called from the current top state in the state machine's state stack (See StateMachine::_states).
         */
        void Run();

#pragma region Game State

    private:
        /**
         * Pointer to the instance of core game data that will be used throughout the game.
         */
        CoreGameData* _coreGameData;

#pragma endregion

#pragma region Window Settings

    private:
        /**
         * Variable to limit the framerate. Will always be used.
         */
        unsigned int _framerateLimit = 60;

        /**
         * Variable to limit physics updates to a fixed ms timestep. Updates will only happen every `_timestep` ms.
         */
        float _timestep = 1.0f / 60.0f;

#pragma endregion

#pragma region Lower Level Window Variables

    private:
        /**
         * SFML Clock instance of the game.
         */
        sf::Clock _clock;

        sf::View _view;

#pragma endregion
    };
} // namespace he

#endif // GAME_HPP
