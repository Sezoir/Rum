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
        /**
         * @brief Initialise the input, such as the event system.
         */
        void init();

        /**
         * @brief Check whether a key is pressed.
         * @param key: The key you want to check is pressed.
         * @return bool: - True if the key is currently pressed.
         *               - False if the key is currently released.
         */
        bool isKeyPressed(Keyboard::Key key);

        /**
         * @brief Retrieve the current position of the cursor in the window.
         * @return glm::vec2: (x,y) position of the cursor.
         */
        glm::vec2 getCursorPosition();

        /**
         * @brief Retrieve the current offset of the mouse wheel.
         * @return glm::vec2: (x,y) offset of the mouse wheel.
         */
        glm::vec2 getMouseOffset();

        /**
         * @brief Check whether a mouse button is pressed.
         * @param button: The button you want to check is pressed.
         * @return bool: - True if the button is currently pressed.
         *               - False if the button is currently released.
         */
        bool isMousePressed(Mouse::Button button);

        /**
         * @brief Event callback for receiving event updates.
         * @param event: An Event update.
         */
        void onEvent(const Events::Event& event) override;

    private:
        /**
         * @brief Handles the keyboard events.
         * @param event: An keyboard related event.
         */
        void handleKeyboardEvent(const Events::Event& event);

        /**
         * @brief Handles mouse events.
         * @param event: An mouse related event.
         */
        void handleMouseEvent(const Events::Event& event);

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
