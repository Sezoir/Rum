#pragma once
// Std libs
#include <memory>
// External libs
#include <SFML/Window.hpp>
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

        // Disable copying
        WindowsWindow(WindowsWindow const&) = delete;
        WindowsWindow& operator=(const WindowsWindow&) = delete;

        bool init() override;

        [[nodiscard]] bool isOpen() const override;

        void pollInput() override;

    private:
        std::unique_ptr<sf::Window> mWindow = nullptr;

        Core::WindowConfig mConfig;
    };
} // namespace Rum::Platform
