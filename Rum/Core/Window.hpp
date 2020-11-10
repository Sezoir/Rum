#pragma once
// Std libs
#include <memory>
// External libs
#include <SFML/Window.hpp>
// Project files
#include "Events/WindowEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "RObject.hpp"
//#include "Events/Event.hpp"

namespace Rum::Core
{
    class Window : public RObject
    {
    public:
        Window();

        // Disable copying
        Window(Window const&) = delete;
        Window& operator=(const Window&) = delete;

        bool init();

        [[nodiscard]] bool isOpen() const;

        void pollInput();

    private:
        std::unique_ptr<sf::Window> mWindow = nullptr;
    };
} // namespace Rum::Core
