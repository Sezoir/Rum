// Project files
#include "Window.hpp"
#include "Log.hpp"

namespace Rum::Core
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
        sf::Event event{};
        while(mWindow->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::EventType::Closed:
                {
                    mWindow->close();
                    break;
                }
                case sf::Event::EventType::KeyPressed:
                {
                    Events::KeyPressedEvent eve(event.key);
                    notify(eve);
                    break;
                }
                case sf::Event::EventType::KeyReleased:
                {
                    Events::KeyReleasedEvent eve(event.key);
                    notify(eve);
                    break;
                }
                case sf::Event::EventType::Resized:
                {
                    Events::WindowResizeEvent eve(event.size.width, event.size.height);
                    notify(eve);
                    break;
                }
                default:
                {
                    RUM_CORE_WARN("Event type not registered: {}", event.type);
                    break;
                }
            }
        }
    }
} // namespace Rum::Core
