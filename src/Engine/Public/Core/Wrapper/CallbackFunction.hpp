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
        virtual void Execute(Component* component) const;

        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        virtual void operator()(Component* component) const;

    protected:
        void (*Callback)(Component*);
    };
} // namespace he

#endif // HE_CALLBACK_FUNCTION_HPP
