#include "Application.hpp"
#include "Log.hpp"

namespace Rum::Core
{
    // Initialise pointer to itself as nullptr, as no application has been created yet
    Application* Application::mEngine = nullptr;

    Application::Application()
        : mWindow(std::move(Window::create()))
    {
        // Updated pointer to itself
        Application::mEngine = this;

        // Initialise logging
        Rum::Core::Log::init();

        // Initialise window
        mWindow->init();

        // Initialise input
        mInput.init();
    }

    Application::~Application()
    {
        Application::mEngine = nullptr;
    }

    void Application::run()
    {
        // Testing logging @todo: remove in future
        RUM_CORE_INFO("Testing logging");
        RUM_CORE_TRACE("Testing tracing");
        RUM_CORE_ERROR("Testing error");
        RUM_CORE_CRITICAL("Testing critical");

        RUM_INFO("Testing application logging");
        RUM_ERROR("Error");
        RUM_CRITICAL("Critical");

        // Infinite loop while window is open
        while(mWindow->isOpen())
        {
            // Process Input
            mWindow->pollInput();

            // Update game
            if(Application::getInstance().getInput().isKeyPressed(Keyboard::Key::A))
                RUM_CORE_INFO(true);

            if(Application::getInstance().getInput().isMousePressed(Mouse::Button::Button0))
                RUM_CORE_INFO(true);

            // Render game
            mWindow->update();
        }
    }
    Application& Application::getInstance()
    {
        return *mEngine;
    }

    Input& Application::getInput()
    {
        return mInput;
    }
    Window& Application::getWindow()
    {
        return *mWindow;
    }

} // namespace Rum::Core
