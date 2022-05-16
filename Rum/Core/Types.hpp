#pragma once
#include <chrono>

using namespace std::chrono_literals;

namespace Rum::Core
{
    typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
    typedef std::chrono::microseconds TimeStep;
} // namespace Rum::Core