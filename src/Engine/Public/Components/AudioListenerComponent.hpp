#ifndef HE_AUDIO_LISTENER_COMPONENT_HPP
#define HE_AUDIO_LISTENER_COMPONENT_HPP

#include "Components/AudioSourceComponent.hpp"
#include "Core/Component.hpp"

#include <string>

namespace he
{
    class AudioListenerComponent : public Component
    {
    public:
        float sensitivity = 1.f;

    public:
        AudioListenerComponent(std::string id);

    public:
        /**
         * Initialize the component.
         */
        void Init();

        /**
         * Update function. Called every frame.
         */
        void Update(float dt);

        /**
         * Fixed update function. Called every 1/60 seconds.
         */
        void FixedUpdate(float dt);

    private:
        void PlayAudio(AudioSourceComponent* audioSourceComponent);
    };
} // namespace he

#endif // HE_AUDIO_LISTENER_COMPONENT_HPP
