#include "Core/Wrapper/CallbackFunction.hpp"

namespace he
{
    void CallbackFunction::Execute(Component* component, Component* secondary) const
    {
        return Callback(component, secondary);
    }

    void CallbackFunction::operator()(Component* component, Component* secondary) const
    {
        return Callback(component, secondary);
    }
} // namespace he
