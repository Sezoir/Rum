#include "Window.hpp"

namespace Engine::Core
{

    Window::Window()
    {
    }
    bool Window::init()
    {
        mWindow = std::make_unique<sf::Window>(sf::VideoMode(800, 600), "My window");
        return true;
    }
    bool Window::isOpen() const
    {
        return mWindow->isOpen();
    }
    void Window::pollInput()
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(mWindow->pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                mWindow->close();
            else if(event.key.code == sf::Keyboard::Key::Escape)
                mWindow->close();
        }
    }
} // namespace Engine::Core
