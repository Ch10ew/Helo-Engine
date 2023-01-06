#include "Components/Animation/Frame.hpp"

#include <SFML/Graphics.hpp>

namespace he
{

    Frame::Frame(sf::Sprite sprite, float duration)
        : sprite(sprite), duration(duration)
    {
    }
} // namespace he
