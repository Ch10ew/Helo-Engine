#include "Core/Entity.hpp"

#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/EntityManager.hpp"

#include <typeinfo>

namespace he
{
    Entity::Entity(std::string id)
        : id(id)
    {
    }

    void Entity::AddComponent(std::shared_ptr<Component> component)
    {
        component->Init();

        components.push_back(component.get());
        CoreGameData::GetInstance()->entityManager.AddComponent(std::move(component));
    }

    bool Entity::RemoveComponent(std::string id)
    {
        size_t before = components.size();
        bool result = CoreGameData::GetInstance()->entityManager.RemoveComponent(id);

        if (result)
        {
            components.erase(std::remove_if(
                                 components.begin(), components.end(),
                                 [&](const auto& c)
                                 {
                                     return c->id == id;
                                 }),
                             components.end());
        }

        return (result) && (!(before == components.size()));
    }

} // namespace he
