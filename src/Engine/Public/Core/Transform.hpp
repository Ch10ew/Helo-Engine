#ifndef HE_TRANSFORM_HPP
#define HE_TRANSFORM_HPP

#include <SFML/Graphics.hpp>

namespace he
{
    /**
     * Represents an entity's position, rotation and scale.
     */
    class Transform
    {
    public:
        /**
         * Position of the entity.
         */
        sf::Vector2f position;

        /**
         * Rotation of the entity.
         */
        float rotation = 0.f;

        /**
         * Scale of the entity.
         */
        sf::Vector2f scale;

    public:
        /**
         * @brief Rotate the entity by adding the angle provided. If setting is desired, directly modify the rotation variable.
         *
         * @param degAngle Angle in degrees
         */
        void Rotate(float degAngle);

        /**
         * @brief Scale the entity by multiplying in the factor. If setting is desired, directly modify the scale variable.
         *
         * @param factor Scale factor
         */
        void Scale(sf::Vector2f factor);

        /**
         * @brief Scale the entity by multiplying in the factor. If setting is desired, directly modify the scale variable.
         *
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         */
        void Scale(float factorX, float factorY);
    };
} // namespace he

#endif // HE_TRANSFORM_HPP
