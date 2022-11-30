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
        /**
         * @brief Adds component into the components vector.
         *
         * @param component Component to be added
         */
        bool AddComponent(std::unique_ptr<Component> component);

        /**
         * @brief Remove component with id from the component vector.
         *
         * @param id Id of the component to be removed
         */
        bool RemoveComponent(std::string id);

        /**
         * Sort Components in `components` by priority and component type.
         *
         * Call before updating components. Failure to do so may result in undefined behavior.
         */
        void SortComponents();

    public:
        /**
         * @brief Gets the owning Entity for a component
         *
         * @param component Component to check for
         */
        Entity* GetOwningEntity(Component* component);
    };
} // namespace he

#endif // HE_ENTITY_MANAGER_HPP
