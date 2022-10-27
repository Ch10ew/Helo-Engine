#ifndef HE_STATE_MACHINE_HPP
#define HE_STATE_MACHINE_HPP

#include "Core/GameState.hpp"

#include <debug_assert.hpp>
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>
#include <stack>

namespace he
{
    /**
     * The means of scene management for the game.
     *
     * When starting the game, ensure there is at least one state in the state machine before calling `Game::Run()`.
     *
     * Implemented as a state stack, where the state at the top of the stack is the active state.
     */
    class StateMachine
    {
    private:
        typedef std::unique_ptr<GameState> GameStateUniquePtr;

    public:
        /**
         * Construct a new State Machine object
         */
        StateMachine();

        /**
         * Destroy the State Machine object
         */
        ~StateMachine();

    public:
        /**
         * Disabled Copy Constructor
         */
        StateMachine(const StateMachine&) = delete;

        /**
         * Disabled assignment operator
         */
        StateMachine& operator=(const StateMachine&) = delete;

    public:
        /**
         * Adds a state to the stack.
         *
         * Common use case is to replace the top state with a new state. In the case where a pause menu is required, a pause state could be added without replacing and popped when unpausing.
         *
         * @param newState Game State to be added, must be a child class of `he::GameState`.
         * @param isReplacing Whether the active state should be replaced with the supplied new state.
         */
        void AddState(GameStateUniquePtr newState, bool isReplacing = true);

        /**
         * Removes the most recent (top) state.
         */
        void RemoveState();

        /**
         * Gets a pointer to the active state.
         *
         * @return GameStateUniquePtr& Pointer to the active state.
         */
        GameStateUniquePtr& GetActiveState();

    public:
        /**
         * Called every frame before any other actions to process the pending state changes. See Game::Run().
         */
        void ProcessStateChanges();

    private:
        /**
         * State stack.
         */
        std::stack<GameStateUniquePtr> _states;

        /**
         * State to be added/replaced.
         */
        GameStateUniquePtr _newState;

    private:
        /**
         * Flag for removing the active state on the next state change.
         */
        bool _isRemoving = false;

        /**
         * Flag for adding the active state on the next state change.
         */
        bool _isAdding = false;

        /**
         * Flag for replacing the active state on the next state change.
         */
        bool _isReplacing = false;

#pragma region Debug Assert

    private:
#define MODULE_STATE_MACHINE_LEVEL 1

        /**
         * Setup for debug assert.
         */
        struct ModuleStateMachine : debug_assert::default_handler,
                                    debug_assert::set_level<MODULE_STATE_MACHINE_LEVEL>
        {
            static void handle(const debug_assert::source_location& loc, const char* expression) noexcept
            {
                spdlog::error("[debug assert] {0}:{1}: Assertion '{2}' failed.", loc.file_name, loc.line_number, expression);
                exit(EXIT_FAILURE);
            }
        };
#undef MODULE_STATE_MACHINE_LEVEL

#pragma endregion
    };
} // namespace he

#endif // HE_STATE_MACHINE_HPP
