#pragma once
// External libs
#include "GLFW/glfw3.h"
// Project files
#include "Core/KeyCodes.hpp"

namespace Rum::Platform::GLFW
{
    /**
     * @brief Converts the glfw scan code for the keyboard to a Rum Key type.
     * @param key: glfw scancode key.
     * @return Core::Keyboard::Key: The associative Rum key.
     */
    const Core::Keyboard::Key getKey(int key);
} // namespace Rum::Platform::GLFW