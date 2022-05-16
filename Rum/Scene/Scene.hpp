#pragma once
// Std libs
#include <vector>
#include <memory>
// External libs
#include <entt/entt.hpp>
// Project files
#include "RObject.hpp"

namespace Rum::Scene
{
    class Entity;

    /**
     * A `Scene` describing some viewpoint or a grouped set of objects representing a view.
     * Examples can include: main menu screen; game world; hud gui.
     */
    class Scene
    {
    public:
        Scene()
            : mRegistry()
        {
        }
        ~Scene() = default;

        std::unique_ptr<Entity> createEntity();
        void registerObject(std::shared_ptr<RObject> drawable);

        void onUpdate(const Core::TimeStep& timestep);
        void onDraw();

        void load();
        void unload();

    private:
        friend class Entity;

        entt::registry mRegistry;
        std::vector<std::shared_ptr<RObject>> mObjects;
    };
} // namespace Rum::Scene
