#include "Scripts/BoardUpdater.hpp"

#include "Components/AudioSourceComponent.hpp"
#include "Components/ClickableComponent.hpp"
#include "Components/SpriteRendererComponent.hpp"
#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"

#include "TicTacToe/Board.hpp"

namespace ttt
{
    void BoardUpdater::Fill1(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 0, 0);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill2(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 1, 0);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill3(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 2, 0);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill4(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 0, 1);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill5(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 1, 1);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill6(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 2, 1);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill7(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 0, 2);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill8(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 1, 2);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

    void BoardUpdater::Fill9(he::Component* component, he::Component* ignore)
    {
        Board::GetInstance()->Place(Piece::X, 2, 2);
        he::Entity* entity = he::CoreGameData::GetInstance()->entityManager.GetOwningEntity(component);
        he::SpriteRendererComponent* spriteRendererComponent = dynamic_cast<he::SpriteRendererComponent*>(entity->GetComponentByClass<he::SpriteRendererComponent>());
        spriteRendererComponent->sprite.setTextureRect(sf::IntRect(0, 256, 256, 256));
        he::AudioSourceComponent* audioSourceComponent = dynamic_cast<he::AudioSourceComponent*>(entity->GetComponentByClass<he::AudioSourceComponent>());
        audioSourceComponent->isPlay = true;
        he::ClickableComponent* clickableComponent = dynamic_cast<he::ClickableComponent*>(component);
        clickableComponent->enabled = false;
    }

} // namespace ttt
