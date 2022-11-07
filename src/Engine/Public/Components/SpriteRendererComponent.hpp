#ifndef HE_SPRITE_RENDERER_COMPONENT_HPP
#define HE_SPRITE_RENDERER_COMPONENT_HPP

#include "Core/Component.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    class SpriteRendererComponent : public Component
    {
    public:
        sf::Sprite* sprite;
    };
} // namespace he

#endif // HE_SPRITE_RENDERER_COMPONENT_HPP
