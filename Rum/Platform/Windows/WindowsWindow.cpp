// Project files
#include "Events/MouseEvent.hpp"
#include "Platform/GLFW/Utility.hpp"
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

        mContext = Renderer::DrawContext::create(mWindow.get());
        mContext->init();

        // Set glfw user pointer for use in window callbacks
        glfwSetWindowUserPointer(window, this);

        // Set context current
        glfwMakeContextCurrent(mWindow.get());

        // Set swap interval
        mContext->setSwapInterval(1);

        // Set the window resize callback
        glfwSetWindowSizeCallback(mWindow.get(), [](GLFWwindow* window, int width, int height) {
            // Required as glfw has no safeguard in cases that height/width is 0
            // So we add our own
            if(height == 0 && width == 0)
            {
                height = 1;
                width = 1;
            }

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
                    event.code = static_cast<Core::Keyboard::Key>(Platform::GLFW::getKey(key));
                    rWindow.notify(Events::KeyPressedEvent(event));
                    break;
                }
                case GLFW_RELEASE:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(Platform::GLFW::getKey(key));
                    rWindow.notify(Events::KeyReleasedEvent(event));
                    break;
                }
                case GLFW_REPEAT:
                {
                    Events::KeyEvent event;
                    event.code = static_cast<Core::Keyboard::Key>(Platform::GLFW::getKey(key));
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

        // Set the window focus callback
        glfwSetWindowFocusCallback(mWindow.get(), [](GLFWwindow* window, int focused) {
            // Get pointer to WindowsWindow class
            WindowsWindow& rWindow = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
            if(focused)
                rWindow.notify(Events::WindowFocusEvent());
            else
                rWindow.notify(Events::WindowLostFocusEvent());
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
        mContext->swapBuffers();
    }

    const Core::WindowConfig& WindowsWindow::getConfig() const
    {
        return mConfig;
    }

    void WindowsWindow::setCursorControl(const Core::CursorConfig& config)
    {
        if(config.isFixed && config.isHidden)
            glfwSetInputMode(mWindow.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else if(!config.isFixed && config.isHidden)
            glfwSetInputMode(mWindow.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        else
            glfwSetInputMode(mWindow.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

} // namespace Rum::Platform
