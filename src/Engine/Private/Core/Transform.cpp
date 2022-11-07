#include "Core/Transform.hpp"

namespace he
{
    void Transform::Rotate(float degAngle)
    {
        rotation += degAngle;
    }

    void Transform::Scale(sf::Vector2f factor)
    {
        scale.x *= factor.x;
        scale.y *= factor.y;
    }

    void Transform::Scale(float factorX, float factorY)
    {
        scale.x *= factorX;
        scale.y *= factorY;
    }
} // namespace he
