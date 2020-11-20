#pragma once
// Std libs
#include <memory>
#include <cstdint>
#include <string>
// Project files
#include "RObject.hpp"

namespace Rum::Core
{
    struct WindowConfig
    {
        uint32_t mWidth = 800;
        uint32_t mHeight = 600;
        std::string mTitle = "Rum Engine";
    };

    class Window : public RObject
    {
    public:
        Window() = default;
        virtual ~Window() = default;

        // Disable copying
        Window(Window const&) = delete;
        Window& operator=(const Window&) = delete;

        virtual bool init() = 0;

        [[nodiscard]] virtual bool isOpen() const = 0;

        virtual void pollInput() = 0;

        virtual void update() = 0;

        static std::unique_ptr<Window> create(const WindowConfig& windowConfig = WindowConfig());
    };
} // namespace Rum::Core
