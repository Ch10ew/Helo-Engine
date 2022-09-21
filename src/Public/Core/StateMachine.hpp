#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "Core/GameState.hpp"

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
    };
} // namespace he

#endif // STATE_MACHINE_HPP
