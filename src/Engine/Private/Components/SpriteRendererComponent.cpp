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
    }

    void SpriteRendererComponent::Init()
    {
    }

    void SpriteRendererComponent::Update(float dt)
    {
        if (!CoreGameData::GetInstance()->entityManager.GetOwningEntity(this))
        {
            return;
        }

        sf::Vector2f position = CoreGameData::GetInstance()->entityManager.GetOwningEntity(this)->transform.position;
        sf::FloatRect spriteRect = sprite.getGlobalBounds();

        sf::Vector2f newSpritePosition;
        newSpritePosition.x = position.x - spriteRect.width / 2;
        newSpritePosition.y = position.y - spriteRect.height / 2;

        sprite.setPosition(newSpritePosition);

        CoreGameData::GetInstance()->window.draw(sprite);
    }

    void SpriteRendererComponent::FixedUpdate(float dt)
    {
    }

} // namespace he
