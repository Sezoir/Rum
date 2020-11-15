// Project files
#include "WindowsWindow.hpp"
#include "Core/Log.hpp"

namespace Rum::Platform
{

    WindowsWindow::WindowsWindow(const Core::WindowConfig& windowConfig)
    {
        mConfig.mHeight = windowConfig.mHeight;
        mConfig.mWidth = windowConfig.mWidth;
        mConfig.mTitle = windowConfig.mTitle;
    }
    bool WindowsWindow::init()
    {
        mWindow = std::make_unique<sf::Window>(sf::VideoMode(mConfig.mWidth, mConfig.mHeight), mConfig.mTitle);
        return true;
    }
    bool WindowsWindow::isOpen() const
    {
        return mWindow->isOpen();
    }
    void WindowsWindow::pollInput()
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
                    Events::KeyEvent keyEvent;
                    // Note that we are using the fact that they both use the same underlying int16_t keycodes
                    //                    RUM_CORE_INFO(static_cast<int16_t>(event.key.code));
                    keyEvent.code = static_cast<Core::Keyboard::Key>(static_cast<int16_t>(event.key.code));
                    keyEvent.alt = event.key.alt;
                    keyEvent.control = event.key.control;
                    keyEvent.shift = event.key.shift;
                    keyEvent.system = event.key.system;
                    Events::KeyPressedEvent eve(keyEvent);
                    notify(eve);
                    break;
                }
                case sf::Event::EventType::KeyReleased:
                {
                    Events::KeyEvent keyEvent;
                    // Note that we are using the fact that they both use the same underlying int16_t keycodes
                    keyEvent.code = static_cast<Core::Keyboard::Key>(static_cast<int16_t>(event.key.code));
                    keyEvent.alt = event.key.alt;
                    keyEvent.control = event.key.control;
                    keyEvent.shift = event.key.shift;
                    keyEvent.system = event.key.system;
                    Events::KeyReleasedEvent eve(keyEvent);
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
                    //                    RUM_CORE_WARN("Event type not registered: {}", event.type);
                    break;
                }
            }
        }
    }
} // namespace Rum::Platform
