#include "Core/Wrapper/CallbackFunction.hpp"

namespace he
{
    void CallbackFunction::Execute(Component* component) const
    {
        return Callback(component);
    }

    void CallbackFunction::operator()(Component* component) const
    {
        return Callback(component);
    }
} // namespace he
