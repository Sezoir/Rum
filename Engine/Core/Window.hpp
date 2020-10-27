#pragma once
// Std libs
#include <memory>
// External libs
#include <SFML/Window.hpp>
// Project files

namespace Engine::Core
{
    class Window
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
} // namespace Engine::Core