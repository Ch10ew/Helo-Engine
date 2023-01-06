#ifndef HE_SPRITE_RENDERER_COMPONENT_HPP
#define HE_SPRITE_RENDERER_COMPONENT_HPP

#include "Core/Component.hpp"

#include <SFML/Graphics.hpp>

#include <string>

namespace he
{
    /**
     * Renders a sprite onto the entity's position.
     */
    class SpriteRendererComponent : public Component
    {
    public:
        /**
         * Create a new SpriteRendererComponent.
         *
         * @param id Unique identifier for the ClickableComponent
         */
        SpriteRendererComponent(std::string id);

    public:
        /**
         * Sprite to be rendered.
         */
        sf::Sprite sprite;

        /**
         * Layer to render the sprite. Higher number denotes a more front layer and vice versa.
         */
        int layer = 0;

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

#endif // HE_SPRITE_RENDERER_COMPONENT_HPP
