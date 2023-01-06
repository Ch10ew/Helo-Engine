#ifndef HE_CALLBACK_METHOD_HPP
#define HE_CALLBACK_METHOD_HPP

#include "Core/Component.hpp"

namespace he
{
    /**
     * Callback (class) method wrapper.
     *
     * Applies to member functions.
     *
     * Use as a pointer (in most cases).
     *
     * `secondary` can be ignored if not used.
     *
     * @tparam T Class that contains the member function to be used as a callback
     */
    template <class T>
    class CallbackMethod : public CallbackFunction
    {
    public:
        /**
         * @brief Construct a new Callback Method object
         *
         * @param object Pointer to instance of T
         * @param Callback Address of function
         */
        CallbackMethod(T* object, void (T::*Callback)(Component* component, Component* secondary));

    public:
        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        void Execute(Component* component, Component* secondary) const;

        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        void operator()(Component* component, Component* secondary) const;

    protected:
        /**
         * Pointer to instance of T
         */
        T* object;

        /**
         * Callback function
         */
        void (T::*method)(Component* component, Component* secondary);
    };

    template <class T>
    CallbackMethod<T>::CallbackMethod(T* object, void (T::*Callback)(Component* component, Component* secondary)) : object(object), method(Callback)
    {
    }

    // Responsible for executing
    template <class T>
    void CallbackMethod<T>::Execute(Component* component, Component* secondary) const
    {
        return (object->*method)(component, secondary);
    }

    template <class T>
    void CallbackMethod<T>::operator()(Component* component, Component* secondary) const
    {
        return (object->*method)(component, secondary);
    }
} // namespace he

#endif // HE_CALLBACK_METHOD_HPP
