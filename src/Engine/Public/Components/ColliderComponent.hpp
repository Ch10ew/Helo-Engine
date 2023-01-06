#ifndef HE_COLLIDER_COMPONENT_HPP
#define HE_COLLIDER_COMPONENT_HPP

#include "Core/Component.hpp"
#include "Core/Wrapper/CallbackFunction.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace he
{
    class ColliderComponent : public Component
    {
    public:
        /**
         * Bounding box for the collider.
         *
         */
        sf::FloatRect bounds = sf::FloatRect(0, 0, 16, 16);

        /**
         * Behavior when there are collisions.
         */
        std::shared_ptr<CallbackFunction> Callback;

        /**
         * If the component is enabled.
         */
        bool enabled = true;

    public:
        ColliderComponent(std::string id);

    public:
        /**
         * Initialize the component.
         */
        void Init();

        /**
         * Update function. Called every frame.
         */
        void Update(float dt);

        /**
         * Fixed update function. Called every 1/60 seconds.
         */
        void FixedUpdate(float dt);
    };
} // namespace he

#endif // HE_COLLIDER_COMPONENT_HPP
