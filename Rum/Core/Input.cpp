#include "Input.hpp"
#include "Application.hpp"
#include "Events/Event.hpp"

namespace Rum::Core
{
    void Input::init()
    {
        Application::getInstance().getWindow().addSubject(*this);
    }

    bool Input::isKeyPressed(const Keyboard::Key key)
    {
        return mKeyboard[static_cast<Keyboard::KeyCode>(key)];
    }

    void Input::onEvent(const Events::Event& event)
    {

        switch(event.getEventCategory())
        {
            case Events::EventCategory::Keyboard | Events::EventCategory::Input:
            {
                handleKeyboardEvent(event);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void Input::handleKeyboardEvent(const Events::Event& event)
    {
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

} // namespace Rum::Core