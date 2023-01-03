#ifndef HE_CLICKABLE_COMPONENT_HPP
#define HE_CLICKABLE_COMPONENT_HPP

#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/EntityManager.hpp"
#include "Core/Wrapper/CallbackFunction.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace he
{
    /**
     * Makes an entity clickable.
     *
     * Behavior that happens after the entity's sprite is clicked can be changed with `Callback`.
     *
     * Please ensure that the owning entity contains a SpriteRendererComponent.
     */
    class ClickableComponent : public Component
    {
    public:
        /**
         * Create a new ClickableComponent.
         *
         * @param id Unique identifier for the ClickableComponent
         */
        ClickableComponent(std::string id);

    public:
        /**
         * Behavior when the entity's sprite is clicked.
         */
        std::shared_ptr<CallbackFunction> Callback;

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

#endif // HE_CLICKABLE_COMPONENT_HPP
