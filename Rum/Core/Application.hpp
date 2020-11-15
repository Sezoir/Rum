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

        void run();

    private:
        std::unique_ptr<Window> mWindow = nullptr;
        Input mInput;
    };
} // namespace Rum::Core
