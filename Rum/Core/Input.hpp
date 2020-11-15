#pragma once
// Std libs
#include <array>
// Project files
#include "KeyCodes.hpp"
#include "RObject.hpp"
#include "Events/KeyEvent.hpp"
#include "Window.hpp"

namespace Rum::Core
{
    class Input : private RObject
    {
    public:
        void init(Window& window);

        bool isKeyPressed(Keyboard::Key key);

        void onEvent(const Events::Event& event) override;

        void handleKeyboardEvent(const Events::Event& event);

    private:
        // Keyboard layout of which keys are currently pressed
        std::array<bool, static_cast<Keyboard::KeyCode>(Keyboard::Key::KeyCount)> mKeyboard = {};
    };

} // namespace Rum::Core
