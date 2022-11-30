#include "Components/SpriteRendererComponent.hpp"

#include "Core/CoreGameData.hpp"
#include "Core/EntityManager.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    void SpriteRendererComponent::Init()
    {
        entityManager = &(CoreGameData::GetInstance()->entityManager);
    }

    void SpriteRendererComponent::Update(float dt)
    {
        // TODO: ~~add a way to get the owning entity from this component~~ use getowningentity()
        sf::Vector2f position = entityManager->GetOwningEntity(this)->transform.position;
        sf::FloatRect spriteRect = sprite->getGlobalBounds();

        sf::Vector2f newSpritePosition;
        newSpritePosition.x = position.x - spriteRect.width / 2;
        newSpritePosition.y = position.y - spriteRect.height / 2;

        sprite->setPosition(newSpritePosition);
    }

    void SpriteRendererComponent::FixedUpdate(float dt)
    {
    }

}
