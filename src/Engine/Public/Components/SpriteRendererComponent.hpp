#ifndef HE_SPRITE_RENDERER_COMPONENT_HPP
#define HE_SPRITE_RENDERER_COMPONENT_HPP

#include "Core/Component.hpp"
#include "Core/EntityManager.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    class SpriteRendererComponent : public Component
    {
    public:
        sf::Sprite* sprite;

    public:
        void Init();
        void Update(float dt);
        void FixedUpdate(float dt);

    private:
        EntityManager* entityManager;
    };
} // namespace he

#endif // HE_SPRITE_RENDERER_COMPONENT_HPP
