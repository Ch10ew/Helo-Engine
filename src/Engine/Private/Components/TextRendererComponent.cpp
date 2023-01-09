#include "Components/TextRendererComponent.hpp"

#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"
#include "Core/EntityManager.hpp"

#include <SFML/Graphics.hpp>

namespace he
{
    TextRendererComponent::TextRendererComponent(std::string id)
        : Component(id)
    {
        priority = -2;
    }

    void TextRendererComponent::Init()
    {
    }

    void TextRendererComponent::Update(float dt)
    {
        if (enabled)
        {
            if (!CoreGameData::GetInstance()->entityManager.GetOwningEntity(this))
            {
                return;
            }

            he::Transform& transform = CoreGameData::GetInstance()->entityManager.GetOwningEntity(this)->transform;
            sf::Vector2f position = transform.position;
            sf::FloatRect textRect = text.getGlobalBounds();

            sf::Vector2f newtextPosition;
            newtextPosition.x = position.x - textRect.width / 2;
            newtextPosition.y = position.y - textRect.height / 2;

            text.setPosition(newtextPosition);
            text.setRotation(transform.rotation);
            text.setScale(transform.scale);

            CoreGameData::GetInstance()->window.draw(text);
        }
    }

    void TextRendererComponent::FixedUpdate(float dt)
    {
    }

} // namespace he
