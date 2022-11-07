#ifndef HE_ENTITY_MANAGER_HPP
#define HE_ENTITY_MANAGER_HPP

#include "Core/Component.hpp"
#include "Core/Entity.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace he
{
    class EntityManager
    {
    public:
        std::vector<Entity> entities;
        std::vector<std::unique_ptr<Component>> components;

    public:
        // TODO: experiment with type_id and derived pointers
        GetEntitiesO();
    };
} // namespace he

#endif // HE_ENTITY_MANAGER_HPP
