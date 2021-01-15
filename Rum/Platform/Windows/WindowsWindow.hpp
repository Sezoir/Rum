#pragma once
// Std libs
#include <memory>
// External libs
#include <GLFW/glfw3.h>
// Project files
#include "Renderer/DrawContext.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Core/Window.hpp"
#include "Core/KeyCodes.hpp"
#include "Core/MouseCodes.hpp"

namespace Rum::Platform
{
    class WindowsWindow : public Core::Window
    {
    public:
        /**
         * @brief Window constructor.
         * @param windowConfig: Configuration for the window.
         */
        explicit WindowsWindow(const Core::WindowConfig& windowConfig);

        /**
         * @brief Window destructor.
         */
        ~WindowsWindow();

        /**
         * @brief Disable copying for Window.
         */
        WindowsWindow(WindowsWindow const&) = delete;
        WindowsWindow& operator=(const WindowsWindow&) = delete;

        /**
         * @brief Window function override to initialises the window.
         * @return bool: - True if initialising is successful.
         *               - False otherwise.
         */
        bool init() override;

        /**
         * @brief Window function override for checking whether window is open.
         * @return bool: - True if window is open.
         *               - False otherwise.
         */
        [[nodiscard]] bool isOpen() const override;

        /**
         * @brief Window function override for polling the input from the window.
         */
        void pollInput() override;

        /**
         * @brief Window function override for updating the window.
         */
        void update() override;

    private:
        /**
         * @brief Deleter for unique_ptr to GLFWwindow.
         */
        struct DestroyWindow
        {
            void operator()(GLFWwindow* ptr)
            {
                glfwDestroyWindow(ptr);
            }
        };

        // Window pointer
        std::unique_ptr<GLFWwindow, DestroyWindow> mWindow = nullptr;

        // DrawContext pointer
        std::unique_ptr<Renderer::DrawContext> mContext = nullptr;

        // Configuration of window
        Core::WindowConfig mConfig;

        // Number of current windows classes
        static uint16_t mWindowCount;
    };
} // namespace Rum::Platform
