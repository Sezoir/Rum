#pragma once
// Project files
#include "Events/Event.hpp"

namespace Rum::Core
{
    /**
     * @brief The idea behind this class to to implement a similar solution to Qt's QObject class, where this will be a
     *        base class that will be inherited by most classes to get access to the event system. This also means that
     *        it can be extended in the future to provide access to other systems as well, for example having a system
     *        to get access to the world state.
     */
    class RObject : public Events::Observer
    {
    };

} // namespace Rum::Core