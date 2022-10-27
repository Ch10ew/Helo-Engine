#ifndef HE_ENTITY_MANAGER_HPP
#define HE_ENTITY_MANAGER_HPP

#include <memory>
#include <vector>

#include "Core/Component.hpp"
#include "Core/Entity.hpp"
#include "Core/System.hpp"

namespace he
{
    class EntityManager
    {
    public:
        std::vector<std::unique_ptr<Entity>> entities;
        std::vector<std::unique_ptr<System>> systems;
        std::vector<std::shared_ptr<Component>> components;
    };
} // namespace he

#endif // HE_ENTITY_MANAGER_HPP
