#pragma once
// Std libs
#include <memory>
// Project files
#include "RObject.hpp"

namespace Rum::Core
{
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

        static std::unique_ptr<Window> create();
    };
} // namespace Rum::Core
