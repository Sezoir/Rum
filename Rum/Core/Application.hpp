#pragma once
// Std libs
#include <memory>
// Project files
#include "Window.hpp"
#include "Input.hpp"
#include "Types.hpp"
#include "Renderer/Renderer.hpp"
#include "Scene/SceneManager.hpp"
#include "Events/Event.hpp"

namespace Rum::Core
{

    class Application : public Events::Observer
    {
    public:
        /**
         * @brief Application constructor.
         */
        Application();

        /**
         * @brief Application destructor.
         */
        ~Application();

        /**
         * @brief Run the application. This should be the last line to run as it enters a infinite while loop,
         *         whilst the application is running.
         */
        int run();

        /**
         * @brief Retrieves the instance of application from the stored static pointer to itself.
         * @return Application&: A reference to the main application.
         */
        static Application& getInstance();

        /**
         * @brief Retrieves a reference to the input for easy access.
         * @return Input&: A reference to the singleton Input class.
         */
        Input& getInput();

        /**
         * @brief Retrieves a reference to the window for easy access.
         * @return Window&: A reference to the singleton Window class.
         */
        Window& getWindow();

        /**
         * @brief Retrieves a reference to the scene manager for easy access.
         * @return SceneManager&: A reference to the singleton SceneManager class.
         */
        Scene::SceneManager& getSceneManager();

        /**
         * @brief Observer on event trigger
         */
        void onEvent(const Events::Event& event) override;

        /**
         * @brief Returns boolean on if the window is focused on
         */
        bool isFocused() const;

    private:
        std::unique_ptr<Window> mWindow = nullptr;
        Input mInput;
        Scene::SceneManager mSceneManager;
        TimePoint mTimePoint;
        bool mFocus = false;

        // Pointer to itself, for use of getInstance function
        static Application* mEngine;
    };
} // namespace Rum::Core
