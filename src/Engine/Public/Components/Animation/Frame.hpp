#ifndef HE_FRAME_HPP
#define HE_FRAME_HPP

#include <SFML/Graphics.hpp>

namespace he
{
    struct Frame
    {
    public:
        Frame() = delete;
        Frame(sf::Sprite sprite, float duration);

    public:
        sf::Sprite sprite;
        float duration;
    };
} // namespace he

#endif // HE_FRAME_HPP
