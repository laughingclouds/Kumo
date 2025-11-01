#include <print>

#include <kumo/StreamWrapper.hpp>

namespace kumo
{
    void PrintOnceStringStream::print()
    {
        std::print("{}", ss.str());

        ss.str("");
        ss.clear();
    }

    void PrintOnceStringStream::println()
    {
        std::println("{}", ss.str());

        ss.str("");
        ss.clear();
    }
} // namespace kumo