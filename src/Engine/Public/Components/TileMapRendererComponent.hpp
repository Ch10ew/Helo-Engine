#ifndef HE_TILE_MAP_RENDERER_COMPONENT_HPP
#define HE_TILE_MAP_RENDERER_COMPONENT_HPP

#include "Core/Component.hpp"

#include <SFML/Graphics.hpp>

// TODO: Sprite animations
// TODO: Tilemap system
// TODO: Tilemap collision

namespace he
{
    class TileMapRendererComponent : public Component
    {
        sf::Sprite tiles;
    };
} // namespace he

#endif // HE_TILE_MAP_RENDERER_COMPONENT_HPP
