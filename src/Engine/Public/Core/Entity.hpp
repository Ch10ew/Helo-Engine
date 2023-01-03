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
         * Disabled Default Constructor.
         */
        Entity() = delete;

        /**
         * Create a new Entity.
         *
         * @param id Unique identifier for the Entity
         */
        Entity(std::string id);

    public:
        /**
         * Meta tag. Unique identifier for this entity. Please ensure uniqueness.
         */
        std::string id;

    public:
        /**
         * Transform of the entity.
         */
        he::Transform transform;

        /**
         * List of components used by the entity.
         */
        std::vector<Component*> components;

    public:
        /**
         * @brief Attach a component to be used by the entity. Ownership of the component will be handed over to EntityManager.
         *
         * @param component Component to be added, owned by EntityManager's components list
         */
        void AddComponent(std::shared_ptr<Component> component);

        /**
         * @brief Detach a component to be used by the entity.
         *
         * @param id ID of the component to be detached
         */
        bool RemoveComponent(std::string id);

        /**
         * @brief Gets a component attached to this entity by a class
         *
         * @return Component* First found component. nullptr if not found
         */
        template <class T>
        Component* GetComponentByClass()
        {
            for (auto component : components)
            {
                if (typeid(*component).hash_code() == typeid(T).hash_code())
                {
                    return component;
                }
            }

            return nullptr;
        }
    };
} // namespace he

#endif // HE_ENTITY_HPP
