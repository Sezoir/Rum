#pragma once
// Std libs
#include <vector>
#include <string>
#include <sstream>
// Project files
#include "Core/Log.hpp"

namespace Rum::Events
{
    // Represents a single bit.
#define BIT(x) 1u << unsigned(x)

    // Adds functions for detecting the type of event. Mostly used for convenience when creating new events.
#define EVENT_CLASS_TYPE(type)                                                                                         \
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

    // Adds functions for detecting the categories of the event. Mostly used for convenience when creating new events.
#define EVENT_CATEGORY_TYPE(category)                                                                                  \
    virtual EventCategory getEventCategory() const override                                                            \
    {                                                                                                                  \
        return category;                                                                                               \
    }

    // The types of events
    enum class EventType
    {
        None,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        KeyPressed,
        KeyReleased,
        MouseMoved,
        MouseScrolled,
        MouseButtonPressed,
        MouseButtonReleased
    };

    // We use bit macro in-case we want to use bitwise operations later
    enum class EventCategory : uint32_t
    {
        None = 0,
        Window = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2),
        Mouse = BIT(3)
    };
    constexpr inline EventCategory operator|(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(static_cast<std::underlying_type<EventCategory>::type>(lhs) |
                                          static_cast<std::underlying_type<EventCategory>::type>(rhs));
    }
    constexpr inline EventCategory operator&(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(static_cast<std::underlying_type<EventCategory>::type>(lhs) &
                                          static_cast<std::underlying_type<EventCategory>::type>(rhs));
    }

    // Simply Event interface for every event to inherit.
    class Event
    {
    public:
        [[nodiscard]] virtual EventType getEventType() const = 0;
        [[nodiscard]] virtual const char* getName() const = 0;
        [[nodiscard]] virtual EventCategory getEventCategory() const = 0;
        [[nodiscard]] virtual std::string toString() const
        {
            return getName();
        }

        /**
         * @brief Used to cast the event to the correct event type as events are passed around as "Event&" instead of
         *        "KeyPressedEvent&".
         * @tparam T: The correct event type.
         * @return T&: Reference which has been correctly casted from itself to the correct event type.
         */
        template <typename T>
        const T& convert() const
        {
            if(auto cast = dynamic_cast<const T*>(this))
            {
                return *cast;
            }
            else
            {
                // Error logging
                RUM_CORE_ERROR("Error: convert function for event {} failed to cast correctly", getName());
                exit(-1); // @TODO: Add custom exit command
            }
        }
    };

    // A basic mixed observer design pattern class which will be used for passing around events.
    class Observer
    {
    public:
        /**
         * @brief Add a class to its subjects. These classes will be notified with an event is given.
         * @param observer: Reference to another observer.
         */
        void addSubject(Observer& observer)
        {
            mSubjects.push_back(&observer);
        }

        /**
         * @brief A virtual function to be overridden which will be called when receiving an event.
         * @param event
         */
        virtual void onEvent(const Event& event)
        {
        }

    protected:
        /**
         * @brief Notifies your subjects of the event.
         * @param event: An event you want to notify yours subjects about.
         */
        void notify(const Event& event)
        {
            for(auto* x : mSubjects)
            {
                x->onEvent(event);
            }
        }

    private:
        // Vector to stored pointers to subjects
        std::vector<Observer*> mSubjects = {};
    };

} // namespace Rum::Events
