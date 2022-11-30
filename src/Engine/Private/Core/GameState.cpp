#include "Core/GameState.hpp"

#include <iostream>

namespace he
{
    void GameState::Update(float dt)
    {
        for (auto& component : entityManager.components)
        {
            component->Update(dt);
        }
    }

    void GameState::FixedUpdate(float dt)
    {
        for (auto& component : entityManager.components)
        {
            component->FixedUpdate(dt);
        }
    }
}
