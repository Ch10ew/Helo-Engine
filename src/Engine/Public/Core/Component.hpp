#ifndef HE_COMPONENT_HPP
#define HE_COMPONENT_HPP

#include <string>
#include <vector>

namespace he
{
    /**
     * Base class for components. A component is owned by EntityManager and subsequently used by Entities.
     */
    class Component
    {
    public:
        /**
         * Unique identifier for the Component
         */
        std::string id;

        /**
         * Update priority for the Component
         */
        int priority;

    public:
        /**
         * Disabled Default Constructor.
         */
        Component() = delete;

        /**
         * Create a new Component.
         *
         * @param id Unique identifier for the Component
         */
        Component(std::string id);

    public:
        virtual void Init(){};
        virtual void Update(float){};
        virtual void FixedUpdate(float){};
    };
} // namespace he

#endif // HE_COMPONENT_HPP
