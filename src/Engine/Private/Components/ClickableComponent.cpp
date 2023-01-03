#include "Components/ClickableComponent.hpp"

#include "Components/SpriteRendererComponent.hpp"
#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"
#include "Core/EntityManager.hpp"

#include <SFML/Graphics.hpp>
#include <aixlog.hpp>

namespace he
{
    ClickableComponent::ClickableComponent(std::string id)
        : Component(id)
    {
        priority = -1;
    }

    void ClickableComponent::Init()
    {
    }

    void ClickableComponent::Update(float dt)
    {
        if (CoreGameData::GetInstance()->eventPolledCurrentFrame)
        {
            if (CoreGameData::GetInstance()->event.type == sf::Event::MouseButtonPressed)
            {
                if (CoreGameData::GetInstance()->event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    Entity* selfEntity = CoreGameData::GetInstance()->entityManager.GetOwningEntity(this);
                    Component* component = selfEntity->GetComponentByClass<SpriteRendererComponent>();
                    if (component)
                    {
                        SpriteRendererComponent* spriteRendererComponent = dynamic_cast<SpriteRendererComponent*>(component);
                        sf::Vector2f mousePos = sf::Vector2f(CoreGameData::GetInstance()->event.mouseButton.x, CoreGameData::GetInstance()->event.mouseButton.y);
                        if (spriteRendererComponent->sprite.getGlobalBounds().contains(mousePos))
                        {
                            if (Callback)
                            {
                                Callback->Execute(this);
                            }
                            else
                            {
                                LOG(WARNING) << "Entity " << selfEntity->id << " clicked but no callback assigned."
                                             << "\n";
                            }
                        }
                    }
                }
            }
        }
    }

    void ClickableComponent::FixedUpdate(float dt)
    {
    }
} // namespace he
