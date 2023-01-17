#include "Components/ColliderComponent.hpp"

#include "Components/SpriteRendererComponent.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

#include <string>
#include <typeinfo>

namespace he
{
    ColliderComponent::ColliderComponent(std::string id)
        : Component(id)
    {
        priority = 5;
    }

    void ColliderComponent::Init()
    {
        Entity* selfEntity = CoreGameData::GetInstance().entityManager.GetOwningEntity(this);
        if (selfEntity)
        {
            SpriteRendererComponent* spriteRendererComponent = dynamic_cast<SpriteRendererComponent*>(selfEntity->GetComponentByClass<SpriteRendererComponent>());
            if (spriteRendererComponent)
            {
                sf::FloatRect spriteRect = spriteRendererComponent->sprite.getGlobalBounds();
                bounds = spriteRect;
            }
        }
    }

    void ColliderComponent::Update(float dt)
    {
        // Update collider position
        Entity* selfEntity = CoreGameData::GetInstance().entityManager.GetOwningEntity(this);
        SpriteRendererComponent* spriteRendererComponent = dynamic_cast<SpriteRendererComponent*>(selfEntity->GetComponentByClass<SpriteRendererComponent>());
        if (spriteRendererComponent)
        {
            sf::FloatRect spriteRect = spriteRendererComponent->sprite.getGlobalBounds();
            bounds = spriteRect;
        }

        // Check collision
        if (enabled)
        {
            if (Callback)
            {
                for (auto& component : CoreGameData::GetInstance().entityManager.components)
                {
                    // Check for collider component
                    if (typeid(*(component.get())).hash_code() == typeid(ColliderComponent).hash_code())
                    {
                        ColliderComponent* colliderComponent = dynamic_cast<ColliderComponent*>(component.get());
                        Entity* otherEntity = CoreGameData::GetInstance().entityManager.GetOwningEntity(colliderComponent);

                        if (colliderComponent->enabled)
                        {
                            // Ignore check if its self
                            if (otherEntity != selfEntity)
                            {
                                // Check bounds
                                ColliderComponent* colliderComponent = dynamic_cast<ColliderComponent*>(otherEntity->GetComponentByClass<ColliderComponent>());
                                if (bounds.intersects(colliderComponent->bounds))
                                {
                                    Callback->Execute(this, colliderComponent);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void ColliderComponent::FixedUpdate(float dt)
    {
    }
} // namespace he
