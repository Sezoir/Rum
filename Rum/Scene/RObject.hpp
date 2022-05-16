#pragma once

#include <chrono>
#include "Core/Types.hpp"
#include "Events/Event.hpp"

namespace Rum::Scene
{

    /**
     * A base parent class for all objects that wish to interact with the `Scene`.
     * This class should never be initialised by itself, but instead be inherited.
     */
    class RObject
    {
    public:
        virtual void update(const Core::TimeStep& timestep){};
        virtual void draw(){};
        virtual void load(){};
        virtual void unload(){};
        virtual void onEvent(const Events::Event& event){};

    private:
        RObject(){};
    };

} // namespace Rum::Scene