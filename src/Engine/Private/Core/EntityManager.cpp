#include "Core/EntityManager.hpp"

#include "Components/SpriteRendererComponent.hpp"
#include "Core/Entity.hpp"

#include <aixlog.hpp>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <typeinfo>
#include <vector>

namespace he
{
    // TODO: unit tests
    void EntityManager::Clear()
    {
        entities.clear();
        components.clear();
    }

    bool EntityManager::AddEntity(std::shared_ptr<Entity> entity)
    {
        for (auto& e : entities)
        {
            if (e->id == entity->id)
            {
                LOG(WARNING) << "Entity with id '" << entity->id << "' already exists! Skipping creation of Entity '" << entity->id << "'\n";
                return false;
            }
        }

        entities.push_back(entity);
        return true;
    }

    bool EntityManager::RemoveEntity(std::string id)
    {
        size_t before = entities.size();
        Entity* selfEntity = GetEntityById(id);

        components.erase(std::remove_if(
                             components.begin(), components.end(),
                             [&](const auto& c)
                             {
                                 return GetOwningEntity(c.get()) == selfEntity;
                             }),
                         components.end());

        entities.erase(std::remove_if(
                           entities.begin(), entities.end(),
                           [&](const auto& e)
                           {
                               return e->id == id;
                           }),
                       entities.end());

        if (!(before == entities.size()))
        {
            LOG(INFO) << "Successfully removed entity\n";
        }
        else
        {
            LOG(WARNING) << "Failed to remove entity! Check the id supplied\n";
        }

        return !(before == entities.size());
    }

    Entity* EntityManager::GetOwningEntity(Component* component)
    {
        if (!component)
        {
            LOG(WARNING) << "Null component pointer provided! Returning nullptr\n";
            return nullptr;
        }

        for (auto& entity : entities)
        {
            for (auto& tmpComponent : entity->components)
            {
                if (tmpComponent == component)
                {
                    return entity.get();
                }
            }
        }

        return nullptr;
    }

    Component* EntityManager::GetComponentById(std::string id)
    {
        for (auto& component : components)
        {
            if (component->id == id)
            {
                return component.get();
            }
        }

        return nullptr;
    }

    Entity* EntityManager::GetEntityById(std::string id)
    {
        for (auto& entity : entities)
        {
            if (entity->id == id)
            {
                return entity.get();
            }
        }

        return nullptr;
    }

    bool EntityManager::AddComponent(std::shared_ptr<Component> component)
    {
        for (auto& c : components)
        {
            if (c->id == component->id)
            {
                LOG(WARNING) << "Component with id '" << component->id << "' already exists! Skipping creation of Component '" << component->id << "'\n";
                return false;
            }
        }

        components.push_back(std::move(component));
        SortComponents();
        return true;
    }

    bool EntityManager::RemoveComponent(std::string id)
    {
        size_t before = components.size();
        components.erase(std::remove_if(
                             components.begin(), components.end(),
                             [&](const auto& c)
                             {
                                 return c->id == id;
                             }),
                         components.end());

        return !(before == components.size());
    }

    void EntityManager::SortComponents()
    {
        // Get hashes of all types of components
        std::map<int, std::set<size_t>> priorityComponentHashMap;
        std::set<size_t> uniqueHashes;
        for (auto& component : components)
        {
            priorityComponentHashMap[component.get()->priority].insert(typeid(*(component.get())).hash_code());
            uniqueHashes.insert(typeid(*(component.get())).hash_code());
        }

        // sort in tmp vector
        std::vector<std::shared_ptr<Component>> tmpComponents;
        for (auto kvit = priorityComponentHashMap.rbegin(); kvit != priorityComponentHashMap.rend(); kvit++)
        {
            for (int x = 0; x < components.size(); ++x)
            {
                auto& set = kvit->second;
                if (components[x] && set.find(typeid(*(components[x].get())).hash_code()) != set.end())
                {
                    tmpComponents.push_back(std::move(components[x]));
                }
            }
        }

        std::vector<std::shared_ptr<Component>> tmpComponents2;
        std::vector<std::shared_ptr<Component>> tmpSpriteRendererComponents; // for custom renderling layer sort
        bool isEnteredSpriteRendererComponentsSection;
        bool isExitedSpriteRendererComponentsSection;
        if (uniqueHashes.find(typeid(SpriteRendererComponent).hash_code()) != uniqueHashes.end())
        {
            for (int x = 0; x < tmpComponents.size(); ++x)
            {
                // check for sprite renderer component and add to separate list, then combine at the end
                if (typeid(*(tmpComponents[x].get())).hash_code() == typeid(SpriteRendererComponent).hash_code())
                {
                    // Entered/In SpriteRendererComponent section
                    isEnteredSpriteRendererComponentsSection = true;
                    tmpSpriteRendererComponents.push_back(std::move(tmpComponents[x]));
                }
                else if (isEnteredSpriteRendererComponentsSection)
                {
                    // Upon exit
                    isExitedSpriteRendererComponentsSection = true;

                    // Resort the SpriteRendererComponents
                    std::sort(
                        tmpSpriteRendererComponents.begin(),
                        tmpSpriteRendererComponents.end(),
                        [](std::shared_ptr<Component>& a, std::shared_ptr<Component>& b)
                        { return (dynamic_cast<SpriteRendererComponent*>(a.get())->layer < dynamic_cast<SpriteRendererComponent*>(b.get())->layer); });

                    // Reattach the SpriteRendererComponents into the tmpComponents
                    for (auto& spriteRendererComponent : tmpSpriteRendererComponents)
                    {
                        tmpComponents2.push_back(std::move(spriteRendererComponent));
                    }
                    tmpSpriteRendererComponents.clear();

                    // Default behavior (after exiting the SpriteRendererComponent section)
                    tmpComponents2.push_back(std::move(tmpComponents[x]));
                }
                else
                {
                    // Default behavior
                    tmpComponents2.push_back(std::move(tmpComponents[x]));
                }
            }
            // Reattach the SpriteRendererComponents into the tmpComponents (in case SpriteRendererComponent is the last component)
            std::sort(
                tmpSpriteRendererComponents.begin(),
                tmpSpriteRendererComponents.end(),
                [](std::shared_ptr<Component>& a, std::shared_ptr<Component>& b)
                { return (dynamic_cast<SpriteRendererComponent*>(a.get())->layer < dynamic_cast<SpriteRendererComponent*>(b.get())->layer); });

            for (auto& spriteRendererComponent : tmpSpriteRendererComponents)
            {
                tmpComponents2.push_back(std::move(spriteRendererComponent));
            }
        }

        // rebuild components vector
        components.clear();
        for (auto& component : tmpComponents2)
        {
            components.push_back(std::move(component));
        }
    }
} // namespace he
