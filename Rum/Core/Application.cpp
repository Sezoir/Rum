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

        // Init renderer
        Renderer::Renderer::init();

        // Initialise window
        mWindow->init();

        // Initialise input
        mInput.init();

        // Listen to window
        mWindow->addSubject(*this);
    }

    Application::~Application()
    {
        Application::mEngine = nullptr;
    }

    int Application::run()
    {
        // Testing logging @todo: remove in future
        RUM_CORE_INFO("Testing logging");
        RUM_CORE_TRACE("Testing tracing");
        RUM_CORE_ERROR("Testing error");
        RUM_CORE_CRITICAL("Testing critical");

        RUM_INFO("Testing application logging");
        RUM_ERROR("Error");
        RUM_CRITICAL("Critical");

        mTimePoint = std::chrono::system_clock::now();
        // Infinite loop while window is open
        while(mWindow->isOpen())
        {
            // Process Input
            mWindow->pollInput();

            // Calculate time step
            TimeStep timeStep = std::chrono::duration_cast<TimeStep>(std::chrono::system_clock::now() - mTimePoint);

            // Update game
            mWindow->update();
            mSceneManager.onUpdate(timeStep);

            // Render game
            Renderer::Renderer::getAPI()->setClearColour({0.2f, 0.3f, 0.3f, 1.0f});
            Renderer::Renderer::getAPI()->clear();
            mSceneManager.onDraw();
        }
        return 0;
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

    Scene::SceneManager& Application::getSceneManager()
    {
        return mSceneManager;
    }

    void Application::onEvent(const Events::Event& event)
    {
        switch(event.getEventType())
        {
            case Events::EventType::WindowFocus:
            {
                mFocus = true;
                break;
            }
            case Events::EventType::WindowLostFocus:
            {
                mFocus = false;
                break;
            }
            default:
                break;
        }
    }

    bool Application::isFocused() const
    {
        return mFocus;
    }

    Renderer::ShaderManager& Application::getShaderManager()
    {
        return mShaderManager;
    }

} // namespace Rum::Core
