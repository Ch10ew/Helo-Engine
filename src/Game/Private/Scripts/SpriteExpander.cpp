#include "Scripts/SpriteExpander.hpp"

#include "Components/ClickableComponent.hpp"
#include "Components/SpriteRendererComponent.hpp"
#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"

#include <SFML/Graphics.hpp>

#include <string>

namespace ttt
{
    void SpriteExpander::Callback(he::Component* component, he::Component* ignore)
    {
        he::Entity* selfEntity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);

        he::Component* spriteRendererComponentPtr = selfEntity->GetComponentByClass<he::SpriteRendererComponent>();
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(spriteRendererComponentPtr);

        spriteRendererComponent->sprite.scale(1.25f, 1.25f);
    }
} // namespace ttt
