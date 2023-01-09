#ifndef HE_TEXT_RENDERER_COMPONENT_HPP
#define HE_TEXT_RENDERER_COMPONENT_HPP

#include "Core/Component.hpp"

#include <SFML/Graphics.hpp>

#include <string>

namespace he
{
    /**
     * Renders a text onto the entity's position.
     */
    class TextRendererComponent : public Component
    {
    public:
        /**
         * Create a new SpriteRendererComponent.
         *
         * @param id Unique identifier for the ClickableComponent
         */
        TextRendererComponent(std::string id);

    public:
        /**
         * Sprite to be rendered.
         */
        sf::Text text;

        /**
         * Layer to render the sprite. Higher number denotes a more front layer and vice versa.
         */
        int layer = 0;

        /**
         * If the component is enabled.
         */
        bool enabled = true;

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

#endif // HE_TEXT_RENDERER_COMPONENT_HPP
