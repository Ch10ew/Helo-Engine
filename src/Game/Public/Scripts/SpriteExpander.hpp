#ifndef TTT_SPRITE_EXPANDER_HPP
#define TTT_SPRITE_EXPANDER_HPP

#include "Core/Component.hpp"

#include <functional>
#include <string>

namespace ttt
{
    /**
     * User created script to expand a sprite when clicked.
     *
     * Contains a callback function for ClickableComponent to act upon.
     */
    class SpriteExpander
    {
    public:
        /**
         * @brief Expands the sprite's scale by 1.25.
         *
         * @param component Caller component
         */
        void Callback(he::Component* component);
    };
} // namespace ttt

#endif // TTT_SPRITE_EXPANDER_HPP
