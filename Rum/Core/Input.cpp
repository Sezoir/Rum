#include <Events/MouseEvent.hpp>
#include "Input.hpp"
#include "Application.hpp"

namespace Rum::Core
{
    void Input::init(Window* window)
    {
        // Check if window is provided
        if(window == nullptr)
        {
            // Subscribe to window event notifications
            Application::getInstance().getWindow().addSubject(*this);
        }
        else
        {
            window->addSubject(*this);
        }
    }

    // Ignore warning about case value not in enumerated type 'Rum::Events::EventCategory' since we are using
    // enum to represent seperate bits
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"
    void Input::onEvent(const Events::Event& event)
    {
        // Get the category of the event, to know how to process it.
        // The idea behind this is to reduce the amount of event type checks, as well to keep code readable.
        switch(event.getEventCategory())
        {
            case Events::EventCategory::Keyboard | Events::EventCategory::Input:
            {
                handleKeyboardEvent(event);
                break;
            }
            case Events::EventCategory::Mouse | Events::EventCategory::Input:
            {
                handleMouseEvent(event);
                break;
            }
            default:
            {
                break;
            }
        }
    }
#pragma clang diagnostic pop

    void Input::handleKeyboardEvent(const Events::Event& event)
    {
        // Check for the event
        switch(event.getEventType())
        {
            case Events::EventType::KeyPressed:
            {
                auto keyEvent = dynamic_cast<const Events::KeyPressedEvent&>(event);
                mKeyboard[static_cast<Keyboard::KeyCode>(keyEvent.getKey().code)] = true;
                break;
            }
            case Events::EventType::KeyReleased:
            {
                auto keyEvent = dynamic_cast<const Events::KeyReleasedEvent&>(event);
                mKeyboard[static_cast<Keyboard::KeyCode>(keyEvent.getKey().code)] = false;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void Input::handleMouseEvent(const Events::Event& event)
    {
        // Check for the event
        switch(event.getEventType())
        {
            case Events::EventType::MouseMoved:
            {
                auto mouseEvent = dynamic_cast<const Events::MouseMoveEvent&>(event);
                mXMousePos = mouseEvent.getX();
                mYMousePos = mouseEvent.getY();
                break;
            }
            case Events::EventType::MouseScrolled:
            {
                auto mouseEvent = dynamic_cast<const Events::MouseScrolledEvent&>(event);
                mXMouseOffset = mouseEvent.getXOffset();
                mYMouseOffset = mouseEvent.getYOffset();
                break;
            }
            case Events::EventType::MouseButtonPressed:
            {

                auto mouseEvent = dynamic_cast<const Events::MouseButtonPressedEvent&>(event);
                mMouse[static_cast<Mouse::MouseCode>(mouseEvent.getButton())] = true;
                break;
            }
            case Events::EventType::MouseButtonReleased:
            {
                auto mouseEvent = dynamic_cast<const Events::MouseButtonReleasedEvent&>(event);
                mMouse[static_cast<Mouse::MouseCode>(mouseEvent.getButton())] = false;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    bool Input::isKeyPressed(const Keyboard::Key key)
    {
        return mKeyboard[static_cast<Keyboard::KeyCode>(key)];
    }

    glm::vec2 Input::getCursorPosition()
    {
        return {mXMousePos, mYMousePos};
    }

    glm::vec2 Input::getMouseOffset()
    {
        return {mXMouseOffset, mYMouseOffset};
    }

    bool Input::isMousePressed(Mouse::Button button)
    {
        return mMouse[static_cast<Mouse::MouseCode>(button)];
    }

} // namespace Rum::Core