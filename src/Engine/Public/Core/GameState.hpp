#ifndef HE_GAME_STATE_HPP
#define HE_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "Core/EntityManager.hpp"

namespace he
{
    /**
     * Abstract class for game states.
     *
     * Inherit from this class to make a game state.
     */
    class GameState
    {
    public:
        /**
         * EntityManager of the scene
         */
        EntityManager entityManager;

    public:
        /**
         * Game State default constructor
         */
        GameState(){};

        /**
         * Disabled Copy Constructor
         */
        GameState(const GameState&) = delete;

        /**
         * Disabled assignment operator
         */
        GameState& operator=(const GameState&) = delete;

    public:
        /**
         * Function that will be called within the main game loop.
         *
         * Called during the input step of the main game loop.
         *
         * Steps in the main game loop consists of: input, update, render
         */
        virtual void ProcessInput(sf::Event) = 0;

        /**
         * Function that will be called within the main game loop.
         *
         * Called during the update step of the main game loop.
         *
         * Steps in the main game loop consists of: input, update, render
         */
        virtual void Update(float);

        /**
         * Function that will be called within the main game loop.
         *
         * For physics based updates which needs fixed timesteps.
         *
         * Called during the update step of the main game loop.
         *
         * Steps in the main game loop consists of: input, update, render
         */
        virtual void FixedUpdate(float){};

        /**
         * Function that will be called within the main game loop.
         *
         * Called during the render step of the main game loop.
         *
         * Steps in the main game loop consists of: input, update, render
         */
        virtual void Render() = 0;

    public:
        /**
         * Initialization to be carried out for the state. Favor this function for dynamic objects.
         */
        virtual void Init() = 0;

        /**
         * Actions to be taken when the state is paused.
         */
        virtual void Pause(){};

        /**
         * Actions to be taken when the state is resumed.
         */
        virtual void Resume(){};
    };
} // namespace he

#endif // HE_GAME_STATE_HPP
