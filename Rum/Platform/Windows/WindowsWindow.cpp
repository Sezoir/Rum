// Project files
#include <Events/MouseEvent.hpp>
#include "WindowsWindow.hpp"

namespace Rum::Platform
{
    // Count of windows
    uint16_t WindowsWindow::mWindowCount = 0;

    WindowsWindow::WindowsWindow(const Core::WindowConfig& windowConfig)
    {
        // Check if no windows have been created, if not then initialise glfw lib
        if(mWindowCount == 0)
        {
            if(!glfwInit())
                exit(-1);
        }

        // Increase count of windows
        mWindowCount++;

        // Set config properties of window
        mConfig.mHeight = windowConfig.mHeight;
        mConfig.mWidth = windowConfig.mWidth;
        mConfig.mTitle = windowConfig.mTitle;
    }

    WindowsWindow::~WindowsWindow()
    {
        // Check if last window is being destroyed, if so terminated glfw lib
        if(mWindowCount == 1)
            glfwTerminate();

        // Decrease window count
        mWindowCount--;
    }

    bool WindowsWindow::init()
    {
        // Create new window
        auto* window = glfwCreateWindow(mConfig.mWidth, mConfig.mHeight, mConfig.mTitle.c_str(), NULL, NULL);
        mWindow = std::unique_ptr<GLFWwindow, DestroyWindow>(window);

        // Set glfw user pointer for use in window callbacks
        glfwSetWindowUserPointer(window, this);

        // Set context current
        glfwMakeContextCurrent(mWindow.get());

        // Set swap interval @todo: Change to seperate function
        glfwSwapInterval(1);

        // Set the window resize callback
        glfwSetWindowSizeCallback(mWindow.get(), [](GLFWwindow* window, int width, int height) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send WindowResizeEvent
            Events::WindowResizeEvent eve(width, height);
            rWindow.notify(eve);
        });

        // Set the window close callback
        glfwSetWindowCloseCallback(mWindow.get(), [](GLFWwindow* window) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send WindowClose event
            rWindow.notify(Events::WindowCloseEvent());
        });

        // Set the keyboard callback
        glfwSetKeyCallback(mWindow.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send event based on action
            switch(action)
            {
                case GLFW_PRESS:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(rWindow.getKey(key));
                    rWindow.notify(Events::KeyPressedEvent(event));
                    break;
                }
                case GLFW_RELEASE:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(rWindow.getKey(key));
                    rWindow.notify(Events::KeyReleasedEvent(event));
                    break;
                }
                case GLFW_REPEAT:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(rWindow.getKey(key));
                    rWindow.notify(Events::KeyPressedEvent(event));
                    break;
                }
            }
        });

        // Set the cursor position callback
        glfwSetCursorPosCallback(mWindow.get(), [](GLFWwindow* window, double xPos, double yPos) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            rWindow.notify(Events::MouseMoveEvent(xPos, yPos));
        });

        // Set the scroll wheel callback
        glfwSetScrollCallback(mWindow.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            rWindow.notify(Events::MouseScrolledEvent(xOffset, yOffset));
        });

        // Set the mouse buttons callback
        glfwSetMouseButtonCallback(mWindow.get(), [](GLFWwindow* window, int button, int action, int mods) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send event based on action
            switch(action)
            {
                case GLFW_PRESS:
                {
                    rWindow.notify(Events::MouseButtonPressedEvent(static_cast<Core::Mouse::Button>(button)));
                    break;
                }
                case GLFW_RELEASE:
                {
                    rWindow.notify(Events::MouseButtonReleasedEvent(static_cast<Core::Mouse::Button>(button)));
                    break;
                }
            }
        });

        // Return successful initialisation
        return true;
    }

    bool WindowsWindow::isOpen() const
    {
        return !glfwWindowShouldClose(mWindow.get());
    }

    void WindowsWindow::pollInput()
    {
        glfwPollEvents();
    }

    void WindowsWindow::update()
    {
        glfwSwapBuffers(mWindow.get());
    }

    constexpr Core::Keyboard::Key WindowsWindow::getKey(int key)
    {
        /**
         * @todo: Look at shifting this function elsewhere. Maybe to a Platform/GLFW folder with any similar conversion
         *        functions.
         */
        typedef Core::Keyboard::Key Key;
        switch(key)
        {
            case GLFW_KEY_SPACE:
                return Key::Space;
            case GLFW_KEY_APOSTROPHE:
                return Key::Quote; /* ' */
            case GLFW_KEY_COMMA:
                return Key::Comma; /* , */
            case GLFW_KEY_MINUS:
                return Key::Subtract; /* - */
            case GLFW_KEY_PERIOD:
                return Key::Period; /* . */
            case GLFW_KEY_SLASH:
                return Key::Slash; /* / */
            case GLFW_KEY_0:
                return Key::Num0;
            case GLFW_KEY_1:
                return Key::Num1;
            case GLFW_KEY_2:
                return Key::Num2;
            case GLFW_KEY_3:
                return Key::Num3;
            case GLFW_KEY_4:
                return Key::Num4;
            case GLFW_KEY_5:
                return Key::Num5;
            case GLFW_KEY_6:
                return Key::Num6;
            case GLFW_KEY_7:
                return Key::Num7;
            case GLFW_KEY_8:
                return Key::Num8;
            case GLFW_KEY_9:
                return Key::Num9;
            case GLFW_KEY_SEMICOLON:
                return Key::Semicolon; /* ; */
            case GLFW_KEY_EQUAL:
                return Key::Equal; /* = */
            case GLFW_KEY_A:
                return Key::A;
            case GLFW_KEY_B:
                return Key::B;
            case GLFW_KEY_C:
                return Key::C;
            case GLFW_KEY_D:
                return Key::D;
            case GLFW_KEY_E:
                return Key::E;
            case GLFW_KEY_F:
                return Key::F;
            case GLFW_KEY_G:
                return Key::G;
            case GLFW_KEY_H:
                return Key::H;
            case GLFW_KEY_I:
                return Key::I;
            case GLFW_KEY_J:
                return Key::J;
            case GLFW_KEY_K:
                return Key::K;
            case GLFW_KEY_L:
                return Key::L;
            case GLFW_KEY_M:
                return Key::M;
            case GLFW_KEY_N:
                return Key::N;
            case GLFW_KEY_O:
                return Key::O;
            case GLFW_KEY_P:
                return Key::P;
            case GLFW_KEY_Q:
                return Key::Q;
            case GLFW_KEY_R:
                return Key::R;
            case GLFW_KEY_S:
                return Key::S;
            case GLFW_KEY_T:
                return Key::T;
            case GLFW_KEY_U:
                return Key::U;
            case GLFW_KEY_V:
                return Key::V;
            case GLFW_KEY_W:
                return Key::W;
            case GLFW_KEY_X:
                return Key::X;
            case GLFW_KEY_Y:
                return Key::Y;
            case GLFW_KEY_Z:
                return Key::Z;
            case GLFW_KEY_LEFT_BRACKET:
                return Key::LBracket; /* [ */
            case GLFW_KEY_BACKSLASH:
                return Key::Backslash; /* \ */
            case GLFW_KEY_RIGHT_BRACKET:
                return Key::RBracket; /* ] */
            case GLFW_KEY_GRAVE_ACCENT:
                return Key::Grave; /* ` */
            case GLFW_KEY_WORLD_1:
                return Key::World1; /* non-US #1 */
            case GLFW_KEY_WORLD_2:
                return Key::World2; /* non-US #2 */

            /* Function keys */
            case GLFW_KEY_ESCAPE:
                return Key::Escape;
            case GLFW_KEY_ENTER:
                return Key::Enter;
            case GLFW_KEY_TAB:
                return Key::Tab;
            case GLFW_KEY_BACKSPACE:
                return Key::Backspace;
            case GLFW_KEY_INSERT:
                return Key::Insert;
            case GLFW_KEY_DELETE:
                return Key::Delete;
            case GLFW_KEY_RIGHT:
                return Key::Right;
            case GLFW_KEY_LEFT:
                return Key::Left;
            case GLFW_KEY_DOWN:
                return Key::Down;
            case GLFW_KEY_UP:
                return Key::Up;
            case GLFW_KEY_PAGE_UP:
                return Key::PageUp;
            case GLFW_KEY_PAGE_DOWN:
                return Key::PageDown;
            case GLFW_KEY_HOME:
                return Key::Home;
            case GLFW_KEY_END:
                return Key::End;
            case GLFW_KEY_CAPS_LOCK:
                return Key::CapsLock;
            case GLFW_KEY_SCROLL_LOCK:
                return Key::ScrollLock;
            case GLFW_KEY_NUM_LOCK:
                return Key::NumLock;
            case GLFW_KEY_PRINT_SCREEN:
                return Key::PrintScreen;
            case GLFW_KEY_PAUSE:
                return Key::Pause;
            case GLFW_KEY_F1:
                return Key::F1;
            case GLFW_KEY_F2:
                return Key::F2;
            case GLFW_KEY_F3:
                return Key::F3;
            case GLFW_KEY_F4:
                return Key::F4;
            case GLFW_KEY_F5:
                return Key::F5;
            case GLFW_KEY_F6:
                return Key::F6;
            case GLFW_KEY_F7:
                return Key::F7;
            case GLFW_KEY_F8:
                return Key::F8;
            case GLFW_KEY_F9:
                return Key::F9;
            case GLFW_KEY_F10:
                return Key::F10;
            case GLFW_KEY_F11:
                return Key::F11;
            case GLFW_KEY_F12:
                return Key::F12;
            case GLFW_KEY_F13:
                return Key::F13;
            case GLFW_KEY_F14:
                return Key::F14;
            case GLFW_KEY_F15:
                return Key::F15;
            case GLFW_KEY_F16:
                return Key::F16;
            case GLFW_KEY_F17:
                return Key::F17;
            case GLFW_KEY_F18:
                return Key::F18;
            case GLFW_KEY_F19:
                return Key::F19;
            case GLFW_KEY_F20:
                return Key::F20;
            case GLFW_KEY_F21:
                return Key::F21;
            case GLFW_KEY_F22:
                return Key::F22;
            case GLFW_KEY_F23:
                return Key::F23;
            case GLFW_KEY_F24:
                return Key::F24;
            case GLFW_KEY_F25:
                return Key::F25;
            case GLFW_KEY_KP_0:
                return Key::Numpad0;
            case GLFW_KEY_KP_1:
                return Key::Numpad1;
            case GLFW_KEY_KP_2:
                return Key::Numpad2;
            case GLFW_KEY_KP_3:
                return Key::Numpad3;
            case GLFW_KEY_KP_4:
                return Key::Numpad4;
            case GLFW_KEY_KP_5:
                return Key::Numpad5;
            case GLFW_KEY_KP_6:
                return Key::Numpad6;
            case GLFW_KEY_KP_7:
                return Key::Numpad7;
            case GLFW_KEY_KP_8:
                return Key::Numpad8;
            case GLFW_KEY_KP_9:
                return Key::Numpad9;
            case GLFW_KEY_KP_DECIMAL:
                return Key::Decimal;
            case GLFW_KEY_KP_DIVIDE:
                return Key::Divide;
            case GLFW_KEY_KP_MULTIPLY:
                return Key::Multiply;
            case GLFW_KEY_KP_SUBTRACT:
                return Key::Subtract;
            case GLFW_KEY_KP_ADD:
                return Key::Add;
            case GLFW_KEY_KP_ENTER:
                return Key::NumpadEnter;
            case GLFW_KEY_KP_EQUAL:
                return Key::NumpadEqual;
            case GLFW_KEY_LEFT_SHIFT:
                return Key::LShift;
            case GLFW_KEY_LEFT_CONTROL:
                return Key::LControl;
            case GLFW_KEY_LEFT_ALT:
                return Key::LAlt;
            case GLFW_KEY_LEFT_SUPER:
                return Key::LSystem;
            case GLFW_KEY_RIGHT_SHIFT:
                return Key::RSystem;
            case GLFW_KEY_RIGHT_CONTROL:
                return Key::RControl;
            case GLFW_KEY_RIGHT_ALT:
                return Key::RAlt;
            case GLFW_KEY_RIGHT_SUPER:
                return Key::RSystem;
            case GLFW_KEY_MENU:
                return Key::Menu;
            default:
                return Core::Keyboard::Key::Unknown;
        };
    }

} // namespace Rum::Platform
