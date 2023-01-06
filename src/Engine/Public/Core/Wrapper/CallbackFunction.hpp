#ifndef HE_CALLBACK_FUNCTION_HPP
#define HE_CALLBACK_FUNCTION_HPP

#include "Core/Component.hpp"

namespace he
{
    /**
     * Callback function wrapper.
     *
     * Applies to normal functions.
     *
     * Use as a pointer (in most cases).
     */
    class CallbackFunction
    {
    public:
        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        virtual void Execute(Component* component, Component* secondary) const;

        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        virtual void operator()(Component* component, Component* secondary) const;

    protected:
        void (*Callback)(Component*, Component*);
    };
} // namespace he

#endif // HE_CALLBACK_FUNCTION_HPP
