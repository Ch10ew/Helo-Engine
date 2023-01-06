#include "Components/Animation/AnimationState.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace he
{
    AnimationState::AnimationState(std::string id)
        : id(id)
    {
    }

    AnimationState::AnimationState(const AnimationState& animationState)
    {
        currentSprite = animationState.currentSprite;
        frames = animationState.frames;
        id = animationState.id;
        isLoop = animationState.isLoop;
        timeTracker = animationState.timeTracker;
    }

    void AnimationState::operator=(const AnimationState& animationState)
    {
        currentSprite = animationState.currentSprite;
        frames = animationState.frames;
        id = animationState.id;
        isLoop = animationState.isLoop;
        timeTracker = animationState.timeTracker;
    }

    void AnimationState::AddFrame(sf::Sprite sprite, float duration)
    {
        frames.push_back(Frame(sprite, duration));
    }

    void AnimationState::AddFrame(Frame frame)
    {
        frames.push_back(frame);
    }

    sf::Sprite AnimationState::GetCurrentSprite()
    {
        return frames.at(currentSprite).sprite;
    }

    void AnimationState::Update(float dt)
    {
        if (currentSprite < frames.size())
        {
            timeTracker -= dt;
            if (timeTracker <= 0.f)
            {
                // If not last frame and not looping, advance
                if (currentSprite != frames.size() - 1 || isLoop)
                {
                    currentSprite = (currentSprite + 1) % frames.size();
                }

                timeTracker = frames.at(currentSprite).duration;
            }
        }
    }
} // namespace he
