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
        /**
         * Unique identifier for the Component
         */
        std::string id;

        /**
         * Update priority for the Component
         */
        int priority = 0;

    public:
        /**
         * Initialize the component.
         */
        virtual void Init(){};

        /**
         * Update function. Called every frame.
         */
        virtual void Update(float){};

        /**
         * Fixed update function. Called every 1/60 seconds.
         */
        virtual void FixedUpdate(float){};
    };
} // namespace he

#endif // HE_COMPONENT_HPP
