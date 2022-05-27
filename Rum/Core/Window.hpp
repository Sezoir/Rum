#pragma once
// Std libs
#include <memory>
#include <cstdint>
#include <string>
// Project files
#include "Events/Event.hpp"

namespace Rum::Core
{
    struct WindowConfig
    {
        uint32_t mWidth = 800;
        uint32_t mHeight = 600;
        std::string mTitle = "Rum Engine";
    };

    class Window : public Rum::Events::Observer
    {
    public:
        /**
         * @brief Window constructor.
         */
        Window() = default;

        /**
         * @brief Window destructor.
         */
        virtual ~Window() = default;

        /**
         * @brief Disable copy constructors.
         */
        Window(Window const&) = delete;
        Window& operator=(const Window&) = delete;

        /**
         * @brief Interface function for initialising the window.
         * @return bool: - True if initialising is successful.
         *               - False otherwise.
         */
        virtual bool init() = 0;

        /**
         * @brief Interface function for checking whether window is open.
         * @return bool: - True if window is open.
         *               - False otherwise.
         */
        [[nodiscard]] virtual bool isOpen() const = 0;

        /**
         * @brief Interface function for polling the input from the window.
         */
        virtual void pollInput() = 0;

        /**
         * @brief Interface function for updating the window.
         */
        virtual void update() = 0;

        /**
         * @brief Creates and returns an instance to a new window, based on the platform you are compiling for.
         * @param windowConfig: Configuration for the window.
         * @return std::unique_ptr<Window>: Pointer to the platform window class instance.
         */
        static std::unique_ptr<Window> create(const WindowConfig& windowConfig = WindowConfig());
    };
} // namespace Rum::Core
