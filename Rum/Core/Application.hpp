#pragma once
// Std libs
#include <memory>
// Project files
#include "Window.hpp"
#include "Input.hpp"

namespace Rum::Core
{
    class Application
    {
    public:
        Application();

        ~Application();

        void run();

        static Application& getInstance();

        Input& getInput();

        Window& getWindow();

    private:
        std::unique_ptr<Window> mWindow = nullptr;
        Input mInput;

        static Application* mEngine;
    };
} // namespace Rum::Core
