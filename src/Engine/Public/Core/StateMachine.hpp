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
    class StateMachine
    {
    private:
        typedef std::unique_ptr<GameState> GameStateUniquePtr;

    public:
        StateMachine();
        ~StateMachine();

        StateMachine(const StateMachine&) = delete;
        StateMachine& operator=(const StateMachine&) = delete;

    public:
        void AddState(GameStateUniquePtr newState, bool isReplacing = true);
        void RemoveState();
        GameStateUniquePtr& GetActiveState();

    public:
        /**
         * @brief Called every frame before any other actions to process the pending state changes. See Game::Run().
         *
         */
        void ProcessStateChanges();

    private:
        std::stack<GameStateUniquePtr> _states;
        GameStateUniquePtr _newState;

        bool _isRemoving = false;
        bool _isAdding = false;
        bool _isReplacing = false;

#pragma region Debug Assert

    private:
#define MODULE_STATE_MACHINE_LEVEL 1
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
