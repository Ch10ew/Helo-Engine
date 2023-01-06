#ifndef HE_AUDIO_SOURCE_COMPONENT_HPP
#define HE_AUDIO_SOURCE_COMPONENT_HPP

#include "Core/Component.hpp"

#include <SFML/Audio.hpp>

#include <string>

namespace he
{
    /**
     * Stores music onto an entity to be played.
     *
     * Plays whatever is set.
     * If `music` is set and `sound` is null, then `music` will be played.
     * If both are set, then both will be played.
     *
     * `isSpatialSound` lets a sound be spatial (by distance).
     * If turned off, the sound will be played as if the "distance" is 0.
     *
     * `isLoop` applies to both variables.
     */
    class AudioSourceComponent : public Component
    {
    public:
        AudioSourceComponent(std::string id);

    public:
        sf::Sound sound;
        sf::Music music;

        bool isSpatialSound = true;
        bool isLoop = false;
        bool isPlay = false;
    };
} // namespace he

#endif // HE_AUDIO_SOURCE_COMPONENT_HPP
