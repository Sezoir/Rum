#include "Application.hpp"
#include "Log.hpp"

namespace Rum::Core
{
    Application::Application()
        : mWindow(std::move(Window::create()))
    {
    }

    void Application::run()
    {
        Rum::Core::Log::init();

        RUM_CORE_INFO("Testing logging");
        RUM_CORE_TRACE("Testing tracing");
        RUM_CORE_ERROR("Testing error");
        RUM_CORE_CRITICAL("Testing critical");

        RUM_INFO("Testing application logging");
        RUM_ERROR("Error");
        RUM_CRITICAL("Critical");

        mWindow->init();

        while(mWindow->isOpen())
        {
            // Process Input
            mWindow->pollInput();

            // Update game

            // Render game
        }
    }
} // namespace Rum::Core
