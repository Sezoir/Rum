#pragma once
// Std libs
#include <memory>
// Project files
#include "Window.hpp"

namespace Rum::Core
{
    class Application
    {
    public:
        Application();

        void run();

    private:
        std::unique_ptr<Window> mWindow = nullptr;
    };
} // namespace Rum::Core
