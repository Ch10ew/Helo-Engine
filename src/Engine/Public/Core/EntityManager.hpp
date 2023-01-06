#ifndef HE_ENTITY_MANAGER_HPP
#define HE_ENTITY_MANAGER_HPP

#include "Core/Component.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace he
{
    class Entity; // forward declaration for Entity

    /**
     * Manager for entities.
     *
     * Contains all living entities in the game, regardless of state.
     *
     * Only add entities using this class. Components should be added via Entity.AddComponent().
     */
    class EntityManager
    {
    public:
        /**
         * Existing entities in the game.
         */
        std::vector<std::shared_ptr<Entity>> entities;

        /**
         * Existing components in the game.
         */
        std::vector<std::shared_ptr<Component>> components;

    public:
        /**
         * Clears the entity manager's entities and components.
         */
        void Clear();

    public:
        /**
         * Adds an entity from the entity manager entity vector.
         *
         * @param entity Entity to be added. Will be moved.
         */
        bool AddEntity(std::shared_ptr<Entity> entity);

        /**
         * Removes an entity from the entity manager entity vector.
         *
         * @param id Id of the entity to be removed
         * @return true Successful removal
         * @return false Removal failed
         */
        bool RemoveEntity(std::string id);

    public:
        /**
         * @brief Gets the owning Entity for a component
         *
         * @param component Component to check for
         */
        Entity* GetOwningEntity(Component* component);

        /**
         * @brief Gets a component by its id
         *
         * @param id
         * @return Component*
         */
        Component* GetComponentById(std::string id);

        /**
         * @brief Gets an entity by its id
         *
         * @param id
         * @return Entity*
         */
        Entity* GetEntityById(std::string id);

    public:
        /**
         * Internal use function.
         *
         * Adds a component into the entity manager components vector.
         *
         * @param component Component to be added
         */
        bool AddComponent(std::shared_ptr<Component> component);

        /**
         * Internal use function.
         *
         * Remove a component with id from the entity manager component vector.
         *
         * @param id Id of the component to be removed
         * @return true Successful removal
         * @return false Removal failed
         */
        bool RemoveComponent(std::string id);

        /**
         * Internal use function.
         *
         * Sort Components in `components` by priority and component type.
         *
         * Call before updating components. Failure to do so may result in undefined behavior.
         */
        void SortComponents();
    };
} // namespace he

#endif // HE_ENTITY_MANAGER_HPP
