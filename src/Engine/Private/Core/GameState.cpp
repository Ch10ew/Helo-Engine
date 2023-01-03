#include "Core/GameState.hpp"

#include "Core/CoreGameData.hpp"
#include "Core/EntityManager.hpp"

namespace he
{
    void GameState::Update(float dt)
    {
        for (auto& component : CoreGameData::GetInstance()->entityManager.components)
        {
            component->Update(dt);
        }
    }

    void GameState::FixedUpdate(float dt)
    {
        for (auto& component : CoreGameData::GetInstance()->entityManager.components)
        {
            component->FixedUpdate(dt);
        }
    }
}
