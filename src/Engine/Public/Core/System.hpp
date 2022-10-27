#ifndef HE_SYSTEM_HPP
#define HE_SYSTEM_HPP

#include "Core/Component.hpp"

namespace he
{
    class System
    {
        virtual void Update(float);
        virtual void NotifyComponent(Component*);
    };
} // namespace he

#endif // HE_SYSTEM_HPP
