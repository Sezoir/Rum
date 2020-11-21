#pragma once
// Std libs
#include <array>
// External libs
#include <glm/glm.hpp>
// Project files
#include "KeyCodes.hpp"
#include "MouseCodes.hpp"
#include "RObject.hpp"
#include "Events/KeyEvent.hpp"
#include "Window.hpp"

namespace Rum::Core
{
    class Input : private RObject
    {
    public:
        void init();

        bool isKeyPressed(Keyboard::Key key);

        glm::vec2 getCursorPosition();

        glm::vec2 getMouseOffset();

        bool isMousePressed(Mouse::Button button);

        void onEvent(const Events::Event& event) override;

        void handleKeyboardEvent(const Events::Event& event);

        void handleMouseEvent(const Events::Event& event);

    private:
        // Keyboard layout of which keys are currently pressed
        std::array<bool, Keyboard::KeyCount> mKeyboard = {};

        // Cursor position
        double mXMousePos, mYMousePos = 0;

        // Mouse scroll offset
        double mXMouseOffset, mYMouseOffset = 0;

        // Mouse button layout
        std::array<bool, Mouse::ButtonCount> mMouse = {};
    };

} // namespace Rum::Core
