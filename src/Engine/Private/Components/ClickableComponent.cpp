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
        if (enabled)
        {
            if (CoreGameData::GetInstance()->eventPolledCurrentFrame)
            {
                for (auto& event : CoreGameData::GetInstance()->events)
                {
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Button::Left)
                        {
                            Entity* selfEntity = CoreGameData::GetInstance()->entityManager.GetOwningEntity(this);
                            Component* component = selfEntity->GetComponentByClass<SpriteRendererComponent>();
                            if (component)
                            {
                                SpriteRendererComponent* spriteRendererComponent = dynamic_cast<SpriteRendererComponent*>(component);
                                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                                if (spriteRendererComponent->sprite.getGlobalBounds().contains(mousePos))
                                {
                                    if (Callback)
                                    {
                                        Callback->Execute(this, nullptr);
                                    }
                                    else
                                    {
                                        LOG(WARNING) << "Entity " << selfEntity->id << " clicked but no callback assigned."
                                                     << "\n";
                                    }
                                    break;
                                }
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
