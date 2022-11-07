#include "Core/StateMachine.hpp"

#include <aixlog.hpp>
#include <debug_assert.hpp>

#include <cxxabi.h>

namespace he
{
    StateMachine::StateMachine()
    {
    }

    StateMachine::~StateMachine()
    {
    }

    void StateMachine::AddState(GameStateUniquePtr newState, bool isReplacing)
    {
        _isAdding = true;
        _isReplacing = isReplacing;
        _newState = std::move(newState);

        int status;
        LOG(INFO) << (_isReplacing ? "Replacing" : "Adding")
                  << " state: " << typeid(*(_newState.get())).name() << "\n";
    }

    void StateMachine::RemoveState()
    {
        _isRemoving = true;
        LOG(INFO) << "Removing state " << typeid(*(_states.top().get())).name() << "\n";
    }

    StateMachine::GameStateUniquePtr& StateMachine::GetActiveState()
    {
        // log and terminate if empty at the start (stack is guaranteed not empty during runtime by logic, but initial insertion isnt guaranteed)
        DEBUG_ASSERT(!(_states.empty()), ModuleStateMachine{});

        return _states.top();
    }

    void StateMachine::ProcessStateChanges()
    {
        if (this->_isRemoving && !this->_states.empty())
        {
            this->_states.pop();

            if (!this->_states.empty())
            {
                this->_states.top()->Resume();
            }

            this->_isRemoving = false;
        }

        if (this->_isAdding)
        {
            if (!this->_states.empty())
            {
                if (this->_isReplacing)
                {
                    this->_states.pop();
                }
                else
                {
                    this->_states.top()->Pause();
                }
            }

            this->_states.push(std::move(this->_newState));
            this->_states.top()->Init();
            this->_isAdding = false;
        }
    }
} // namespace he
