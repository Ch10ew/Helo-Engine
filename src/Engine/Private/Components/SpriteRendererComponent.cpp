#include "Components/SpriteRendererComponent.hpp"

#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"
#include "Core/EntityManager.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    SpriteRendererComponent::SpriteRendererComponent(std::string id)
        : Component(id)
    {
        priority = -2;
    }

    void SpriteRendererComponent::Init()
    {
    }

    void SpriteRendererComponent::Update(float dt)
    {
        if (enabled)
        {
            if (!CoreGameData::GetInstance().entityManager.GetOwningEntity(this))
            {
                return;
            }

            he::Transform& transform = CoreGameData::GetInstance().entityManager.GetOwningEntity(this)->transform;
            sf::Vector2f position = transform.position;
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            sf::Vector2f newSpritePosition;
            newSpritePosition.x = position.x - spriteRect.width / 2;
            newSpritePosition.y = position.y - spriteRect.height / 2;

            sprite.setPosition(newSpritePosition);
            sprite.setRotation(transform.rotation);
            sprite.setScale(transform.scale);

            CoreGameData::GetInstance().window.draw(sprite);
        }
    }

    void SpriteRendererComponent::FixedUpdate(float dt)
    {
    }

} // namespace he
