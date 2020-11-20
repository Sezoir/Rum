// Project files
#include "WindowsWindow.hpp"

namespace Rum::Platform
{

    WindowsWindow::WindowsWindow(const Core::WindowConfig& windowConfig)
    {
        mConfig.mHeight = windowConfig.mHeight;
        mConfig.mWidth = windowConfig.mWidth;
        mConfig.mTitle = windowConfig.mTitle;
    }
    bool WindowsWindow::init()
    {
        if(!glfwInit())
            exit(-1);

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

        return true;
    }

    WindowsWindow::~WindowsWindow()
    {
        glfwTerminate();
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
