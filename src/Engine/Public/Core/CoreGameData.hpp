#ifndef HE_CORE_GAME_DATA_HPP
#define HE_CORE_GAME_DATA_HPP

#include "Core/StateMachine.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    /**
     * Singleton that holds the core game data.
     *
     * Not thread-safe.
     *
     * Consists of:
     * - SFML window instance
     * - State Machine instance
     *
     */
    class CoreGameData
    {
    private:
        /**
         * Construct a new Core Game Data object. Private to block new instances from being created.
         */
        CoreGameData();

        /**
         * Destroy the Core Game Data object.
         */
        ~CoreGameData();

    public:
        /**
         * Disabled Copy Constructor
         */
        CoreGameData(CoreGameData& other) = delete;

        /**
         * Disabled assignment operator
         */
        void operator=(const CoreGameData& other) = delete;

        /**
         * Gets the instance of this singleton.
         */
        static CoreGameData* GetInstance();

    public:
        /**
         * SFML Window instance of the game.
         */
        sf::RenderWindow window;

        /**
         * State machine for the game (See StateMachine). Manages the active state and manages state changes in the game.
         */
        StateMachine stateMachine;

        /**
         * EntityManager of the game. Add game entities into the entities attribute of this variable.
         */
        EntityManager entityManager;

        /**
         * Events in the game. Will only change when new events are polled.
         */
        sf::Event event;

        /**
         * Boolean for if any events are polled this frame.
         */
        bool eventPolledCurrentFrame = false;

    protected:
        /**
         * The instance of the singleton.
         */
        static CoreGameData* _instance;
    };
} // namespace he

#endif // HE_CORE_GAME_DATA_HPP
