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
            mWindow.update();
        }
    }
} // namespace Engine::Core
