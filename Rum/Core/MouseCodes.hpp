#pragma once
// Std libs
#include <cstdint>

namespace Rum::Core::Mouse
{
    // The underlying type for Button
    using MouseCode = int16_t;

    // Mouse buttons
    enum class Button : MouseCode
    {
        Button0 = 0,
        Button1,
        Button2,
        Button3,
        Button4,
        Button5,
        Button6,
        Button7,
        ButtonCount //!< Count number of supported buttons. KEEP LAST!!!
    };

    constexpr MouseCode getMouseButtonCount()
    {
        return static_cast<MouseCode>(Button::ButtonCount);
    }
} // namespace Rum::Core::Mouse
