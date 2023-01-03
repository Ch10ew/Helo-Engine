#include "Core/EntityManager.hpp"

#include "Core/Entity.hpp"

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <typeinfo>

#include <iostream>

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
                return false;
            }
        }

        entities.push_back(entity);
        return true;
    }

    bool EntityManager::RemoveEntity(std::string id)
    {
        size_t before = entities.size();
        entities.erase(std::remove_if(
                           entities.begin(), entities.end(),
                           [&](const auto& e)
                           {
                               return e->id == id;
                           }),
                       entities.end());

        return !(before == entities.size());
    }

    Entity* EntityManager::GetOwningEntity(Component* component)
    {
        if (!component)
        {
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

    bool EntityManager::AddComponent(std::shared_ptr<Component> component)
    {
        for (auto& c : components)
        {
            if (c->id == component->id)
            {
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
        for (auto& component : components)
        {
            priorityComponentHashMap[component.get()->priority].insert(typeid(*(component.get())).hash_code());
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

        // rebuild components vector
        components.clear();
        for (auto& component : tmpComponents)
        {
            components.push_back(std::move(component));
        }
    }
} // namespace he
