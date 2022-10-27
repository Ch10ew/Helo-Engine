#ifndef HE_ENTITY_HPP
#define HE_ENTITY_HPP

#include <memory>
#include <string>
#include <vector>

#include "Core/Component.hpp"

namespace he
{
    class Entity
    {
    public:
        std::string id;
        std::vector<std::weak_ptr<Component>> components;
    };
} // namespace he

#endif // HE_ENTITY_HPP
