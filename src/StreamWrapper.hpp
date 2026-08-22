#pragma once
#include <sstream>

namespace kumo {
    template <typename S>
    concept StreamLike = requires(S s, std::string str) {
        { s << str } -> std::same_as<S &>;
    };

    /**`std::stringstream` wrapper that resets `std::stringstream` object after
     * every cout operation.
     * You can write to it using stream operator (<<) but not read from it.
     * This object only prints to stdout.
     */
    class PrintOnceStringStream
    {
        std::stringstream ss;

    public:
        /*Print to stdout and then clear buffer, reset object*/
        void print();
        /*`print()` with newline*/
        void println();

        template <typename T>
            requires requires(std::ostream &os, T &&x) { os << std::forward<T>(x); }
        PrintOnceStringStream &operator<<(T &&v)
        {
            ss << std::forward<T>(v);
            return *this;
        }
};
} // namespace kumo