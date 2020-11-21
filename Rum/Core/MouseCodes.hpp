#pragma once
// Std libs
#include <cstdint>

namespace Rum::Core::Mouse
{
    using MouseCode = int16_t;

    const uint16_t ButtonCount = 8;

    enum class Button : MouseCode
    {
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,
    };
} // namespace Rum::Core::Mouse
