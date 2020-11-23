// Project files
#include <Events/MouseEvent.hpp>
#include "WindowsWindow.hpp"

namespace Rum::Platform
{
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

        auto* window = glfwCreateWindow(mConfig.mWidth, mConfig.mHeight, mConfig.mTitle.c_str(), NULL, NULL);
        mWindow = std::unique_ptr<GLFWwindow, DestroyWindow>(window);

        glfwSetWindowUserPointer(window, this);

        glfwMakeContextCurrent(mWindow.get());
        glfwSwapInterval(1);

        glfwSetWindowSizeCallback(mWindow.get(), [](GLFWwindow* window, int width, int height) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send WindowResizeEvent
            Events::WindowResizeEvent eve(width, height);
            rWindow.notify(eve);
        });

        glfwSetWindowCloseCallback(mWindow.get(), [](GLFWwindow* window) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send WindowClose event
            rWindow.notify(Events::WindowCloseEvent());
        });

        glfwSetKeyCallback(mWindow.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            // Send event based on action
            switch(action)
            {
                case GLFW_PRESS:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(key);
                    rWindow.notify(Events::KeyPressedEvent(event));
                    break;
                }
                case GLFW_RELEASE:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(key);
                    rWindow.notify(Events::KeyReleasedEvent(event));
                    break;
                }
                case GLFW_REPEAT:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(key);
                    rWindow.notify(Events::KeyPressedEvent(event));
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(mWindow.get(), [](GLFWwindow* window, double xPos, double yPos) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            rWindow.notify(Events::MouseMoveEvent(xPos, yPos));
        });

        glfwSetScrollCallback(mWindow.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

            rWindow.notify(Events::MouseScrolledEvent(xOffset, yOffset));
        });

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

} // namespace Rum::Platform
