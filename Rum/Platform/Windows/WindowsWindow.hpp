#pragma once
// Std libs
#include <memory>
// External libs
#include <GLFW/glfw3.h>
// Project files
#include "Events/WindowEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Core/Window.hpp"

namespace Rum::Platform
{
    class WindowsWindow : public Core::Window
    {
    public:
        explicit WindowsWindow(const Core::WindowConfig& windowConfig);
        ~WindowsWindow();

        // Disable copying
        WindowsWindow(WindowsWindow const&) = delete;
        WindowsWindow& operator=(const WindowsWindow&) = delete;

        bool init() override;

        [[nodiscard]] bool isOpen() const override;

        void pollInput() override;

    private:
        struct DestroyWindow
        {
            void operator()(GLFWwindow* ptr)
            {
                glfwDestroyWindow(ptr);
            }
        };

        std::unique_ptr<GLFWwindow, DestroyWindow> mWindow = nullptr;

        Core::WindowConfig mConfig;
    };
} // namespace Rum::Platform
