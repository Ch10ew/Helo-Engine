#ifndef HE_ANIMATION_COMPONENT_HPP
#define HE_ANIMATION_COMPONENT_HPP

#include "Components/Animation/AnimationState.hpp"
#include "Core/Component.hpp"

#include <aixlog.hpp>

#include <map>
#include <string>
#include <vector>

namespace he
{
    /**
     * Sets up state-based animations to be rendered.
     *
     * Uses SpriteRendererComponent's `sprite` variable.
     *
     * Please ensure that the owning entity contains a SpriteRendererComponent.
     */
    class AnimationComponent : public Component
    {
    public:
        struct AnimationStateTrigger
        {
        public:
            std::string fromState;
            std::string toState;

        public:
            AnimationStateTrigger();
            AnimationStateTrigger(std::string fromState, std::string toState);
            AnimationStateTrigger(const AnimationStateTrigger& other);

        public:
            friend bool operator==(const AnimationStateTrigger& lhs, const AnimationStateTrigger& rhs);
            bool operator<(const AnimationStateTrigger& other);
        };

    public:
        /**
         * Create a new AnimationComponent.
         *
         * @param id Unique identifier for the AnimationComponent
         */
        AnimationComponent(std::string id);

    public:
        std::map<std::string, AnimationStateTrigger> stateTriggers;
        std::vector<AnimationState> states;
        AnimationState* currentState = nullptr;
        AnimationState* defaultState = nullptr;

    public:
        /**
         * Adds a state to the animation state vector.
         *
         * @param state State to be added
         */
        void AddState(AnimationState state);

        /**
         * Adds a state trigger (to switch animation states).
         *
         * @param from Id of the source state
         * @param to Id of the destination state
         * @param trigger Name of the trigger
         */
        void AddStateTrigger(std::string from, std::string to, std::string trigger);

        /**
         * Triggers a state change using `trigger`.
         *
         * @param trigger Name of the trigger
         */
        void Trigger(std::string trigger);

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
    };
} // namespace he

#endif // HE_ANIMATION_COMPONENT_HPP
