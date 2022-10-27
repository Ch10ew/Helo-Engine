#ifndef TTT_UTIL_HPP
#define TTT_UTIL_HPP

namespace ttt
{
    class Util
    {
    public:
        static inline int DoNothing(int n) { return n; }
        static inline int Add1(int n) { return ++n; }
        static inline int Sub1(int n) { return --n; }
    };

} // namespace ttt

#endif // TTT_UTIL_HPP
