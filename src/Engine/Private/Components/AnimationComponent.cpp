#include "Components/AnimationComponent.hpp"

#include "Components/SpriteRendererComponent.hpp"
#include "Core/Component.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"
#include "Core/EntityManager.hpp"

#include <string>

namespace he
{
    AnimationComponent::AnimationStateTrigger::AnimationStateTrigger()
    {
    }

    AnimationComponent::AnimationStateTrigger::AnimationStateTrigger(std::string fromState, std::string toState)
        : fromState(fromState), toState(toState)
    {
    }

    AnimationComponent::AnimationStateTrigger::AnimationStateTrigger(const AnimationComponent::AnimationStateTrigger& other)
    {
        fromState = other.fromState;
        toState = other.toState;
    }

    bool operator==(const AnimationComponent::AnimationStateTrigger& lhs, const AnimationComponent::AnimationStateTrigger& rhs)
    {
        return ((lhs.fromState == rhs.fromState) && (lhs.toState == rhs.toState));
    }

    bool AnimationComponent::AnimationStateTrigger::operator<(const AnimationComponent::AnimationStateTrigger& other)
    {
        return (this->fromState < other.fromState);
    }

    AnimationComponent::AnimationComponent(std::string id)
        : Component(id)
    {
    }

    void AnimationComponent::AddState(AnimationState state)
    {
        states.push_back(state);

        if (!defaultState)
        {
            defaultState = &(states.back());
            currentState = defaultState;
        }
    }

    void AnimationComponent::AddStateTrigger(std::string from, std::string to, std::string trigger)
    {
        stateTriggers[trigger] = AnimationComponent::AnimationStateTrigger(from, to);
    }

    void AnimationComponent::Trigger(std::string trigger)
    {
        if (stateTriggers.count(trigger) > 0)
        {
            int newStateIndex = -1;
            int index = 0;
            for (AnimationState state : states)
            {
                if (state.id == stateTriggers[trigger].toState)
                {
                    newStateIndex = index;
                }
                index++;
            }

            if (newStateIndex > -1)
            {
                currentState = &(states.at(newStateIndex));
            }

            return;
        }

        LOG(WARNING) << "Could not find trigger '" << trigger << "'\n";
    }

    void AnimationComponent::Init()
    {
    }

    void AnimationComponent::Update(float dt)
    {
        if (currentState)
        {
            // Update SpriteRendererComponent
            currentState->Update(dt);
            Entity* selfEntity = CoreGameData::GetInstance().entityManager.GetOwningEntity(this);
            SpriteRendererComponent* spriteRendererComponent = dynamic_cast<SpriteRendererComponent*>(selfEntity->GetComponentByClass<SpriteRendererComponent>());
            if (spriteRendererComponent)
            {
                spriteRendererComponent->sprite = currentState->GetCurrentSprite();
            }
        }
    }

    void AnimationComponent::FixedUpdate(float dt)
    {
    }
} // namespace he
