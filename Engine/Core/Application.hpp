#pragma once

// Project files
#include "Window.hpp"

namespace Engine::Core
{
    class Application
    {
    public:
        Application();

        void run();

    private:
        Window mWindow;
    };
} // namespace Engine::Core
