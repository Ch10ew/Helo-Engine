#include "Components/AudioListenerComponent.hpp"

#include "Components/AudioSourceComponent.hpp"
#include "Core/CoreGameData.hpp"
#include "Core/Entity.hpp"

#include <cmath>
#include <string>
#include <typeinfo>

namespace he
{
    AudioListenerComponent::AudioListenerComponent(std::string id)
        : Component(id)
    {
    }

    void AudioListenerComponent::Init()
    {
    }

    void AudioListenerComponent::Update(float dt)
    {
        for (auto& component : CoreGameData::GetInstance()->entityManager.components)
        {
            // Check for audio source component
            if (typeid(*(component.get())).hash_code() == typeid(AudioSourceComponent).hash_code())
            {
                AudioSourceComponent* audioSourceComponent = dynamic_cast<AudioSourceComponent*>(component.get());
                if (audioSourceComponent->isPlay)
                {
                    if (!audioSourceComponent->sound.getBuffer())
                    {
                        return;
                    }

                    // Check for spatial
                    if (audioSourceComponent->isSpatialSound)
                    {
                        Entity* targetEntity = CoreGameData::GetInstance()->entityManager.GetOwningEntity(audioSourceComponent);
                        Entity* selfEntity = CoreGameData::GetInstance()->entityManager.GetOwningEntity(this);

                        float x1 = selfEntity->transform.position.x;
                        float y1 = selfEntity->transform.position.y;
                        float x2 = targetEntity->transform.position.x;
                        float y2 = targetEntity->transform.position.y;

                        audioSourceComponent->sound.setPosition(sf::Vector3f(-(x1 - x2), -(y1 - y2), 0));
                        PlayAudio(audioSourceComponent);
                    }
                    else
                    {
                        audioSourceComponent->sound.setPosition(sf::Vector3f(0.f, 0.f, 0.f));
                        PlayAudio(audioSourceComponent);
                    }
                }
            }
        }
    }

    void AudioListenerComponent::FixedUpdate(float dt)
    {
    }

    void AudioListenerComponent::PlayAudio(AudioSourceComponent* audioSourceComponent)
    {
        if (audioSourceComponent->sound.getStatus() != sf::Sound::Playing)
        {
            audioSourceComponent->sound.setLoop(audioSourceComponent->isLoop);
            audioSourceComponent->sound.play();
        }
        else
        {
            audioSourceComponent->isPlay = false;
        }
    }
} // namespace he
