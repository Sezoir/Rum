#include "Application.hpp"

namespace Engine::Core
{
    Application::Application()
    {
    }

    void Application::run()
    {
        mWindow.init();

        while(mWindow.isOpen())
        {
            // Process Input
            mWindow.pollInput();

            // Update game

            // Render game
        }
    }
} // namespace Engine::Core
