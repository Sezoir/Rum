#pragma once
// Std libs
#include <cstdint>

namespace Rum::Core::Mouse
{
    // The underlying type for Button
    using MouseCode = int16_t;

    // The number of buttons @todo: Make this automatic at compile time, by maybe using macro line count
    const uint16_t ButtonCount = 8;

    // Mouse buttons
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
