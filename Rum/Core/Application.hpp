#pragma once

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
        Window mWindow;
    };
} // namespace Rum::Core
