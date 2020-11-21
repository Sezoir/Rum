#pragma once
// Std libs
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace Rum::Events
{
#define EVENT_FN(fn) [&](Event& event) { fn(event); }
#define BIT(x)       1u << unsigned(x)

#define EVENT_CLASS_TYPE(type)                                                                                         \
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CATEGORY_TYPE(category)                                                                                  \
    virtual EventCategory getEventCategory() const override                                                            \
    {                                                                                                                  \
        return category;                                                                                               \
    }

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

        template <typename T>
        T& convert()
        {
            if(T* cast = dynamic_cast<T*>(this))
            {
                return *cast;
            }
            else
            {
                // Error logging @todo
                std::cout << "Error: convert function for event " << getName() << " failed to cast correctly"
                          << std::endl;
                exit(-1);
            }
        }
    };

    class Observer
    {
    public:
        void addSubject(Observer& observer)
        {
            mSubjects.push_back(&observer);
        }

        virtual void onEvent(const Event& event)
        {
        }

    protected:
        void notify(const Event& event)
        {
            for(auto* x : mSubjects)
            {
                x->onEvent(event);
            }
        }

    private:
        std::vector<Observer*> mSubjects = {};
    };

} // namespace Rum::Events
