#ifndef HE_ANIMATION_STATE_HPP
#define HE_ANIMATION_STATE_HPP

#include "Components/Animation/Frame.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace he
{
    /**
     * A State in the animation State MNachine.
     *
     * Animation frames are stored in the vector `frame`, and will be played in order.
     */
    class AnimationState
    {
    public:
        /**
         * Meta tag. Unique Identifier for this Animation State.
         *
         */
        std::string id;

        /**
         * Frames of the animation
         */
        std::vector<Frame> frames;

        /**
         * Should the animation be looped?
         */
        bool isLoop = false;

    public:
        AnimationState(std::string id);

        AnimationState(const AnimationState& animationState);

        void operator=(const AnimationState& other);

    public:
        /**
         * Adds a frame to be rendered in the animation.
         *
         * @param sprite Sprite to be rendered
         * @param duration Duration to render sprite for
         */
        void AddFrame(sf::Sprite sprite, float duration);

        /**
         * Adds a frame to be rendered in the animation.
         *
         * @param frame Frame to be rendered
         */
        void AddFrame(Frame frame);

        /**
         * Get the sprite for the frame.
         *
         * @return sf::Sprite Sprite to be rendered for the current frame.
         */
        sf::Sprite GetCurrentSprite();

    public:
        /**
         * Internal use function.
         *
         * Updates the current sprite.
         *
         * @param dt Delta time
         */
        void Update(float dt);

    private:
        /**
         * Index of the current sprite in the frame vector.
         */
        int currentSprite = 0;

        /**
         * Keeps track of time left to next frame.
         */
        float timeTracker = 0.f;
    };
} // namespace he

#endif // HE_ANIMATION_STATE_HPP
