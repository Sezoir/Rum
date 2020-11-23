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
        void run();

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

    private:
        std::unique_ptr<Window> mWindow = nullptr;
        Input mInput;

        // Pointer to itself, for use of getInstance function
        static Application* mEngine;
    };
} // namespace Rum::Core
