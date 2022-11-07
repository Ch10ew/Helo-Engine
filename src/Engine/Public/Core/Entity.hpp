#ifndef HE_ENTITY_HPP
#define HE_ENTITY_HPP

#include "Core/Component.hpp"
#include "Core/Transform.hpp"

#include <memory>
#include <string>
#include <vector>

namespace he
{
    class Entity
    {
    public:
        /**
         * Meta tag. Unique identifier for this entity. Please ensure uniqueness.
         */
        std::string id;

    public:
        /**
         * Transform of the entity.
         */
        Transform transform;

        /**
         * List of components used by the entity.
         */
        std::vector<Component*> components;

    public:
        /**
         * @brief Attach a component to be used by the entity. Ownership of the component should be EntityManager.
         *
         * @param component Component to be added, owned by EntityManager's components list
         */
        void AttachComponent(Component* component);

        /**
         * @brief Detach a component to be used by the entity.
         *
         * @param id ID of the component to be detached
         */
        void DetachComponent(std::string id);
    };
} // namespace he

#endif // HE_ENTITY_HPP
