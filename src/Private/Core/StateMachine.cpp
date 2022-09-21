#include "Core/StateMachine.hpp"

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
    }

    void StateMachine::RemoveState()
    {
        _isRemoving = true;
    }

    StateMachine::GameStateUniquePtr& StateMachine::GetActiveState()
    {
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
