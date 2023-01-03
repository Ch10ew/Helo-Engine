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
        CallbackMethod(T* object, void (T::*Callback)(Component* component));

    public:
        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        void Execute(Component* component) const;

        /**
         * @brief Run the callback.
         *
         * @param component Caller component
         */
        void operator()(Component* component) const;

    protected:
        /**
         * Pointer to instance of T
         */
        T* object;

        /**
         * Callback function
         */
        void (T::*method)(Component* component);
    };

    template <class T>
    CallbackMethod<T>::CallbackMethod(T* object, void (T::*Callback)(Component* component)) : object(object), method(Callback)
    {
    }

    // Responsible for executing
    template <class T>
    void CallbackMethod<T>::Execute(Component* component) const
    {
        return (object->*method)(component);
    }

    template <class T>
    void CallbackMethod<T>::operator()(Component* component) const
    {
        return (object->*method)(component);
    }
} // namespace he

#endif // HE_CALLBACK_METHOD_HPP
