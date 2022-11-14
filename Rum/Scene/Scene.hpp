#pragma once
// Std libs
#include <vector>
#include <memory>
// External libs
#include <entt/entt.hpp>
// Project files
#include "RObject.hpp"
#include "Renderer/Camera.hpp"
#include "Renderer/FreeRoamCamera.hpp"

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
            , mCamera(std::make_shared<Renderer::FreeRoamCamera>(90, 0.1, 1000))
        {
        }
        ~Scene() = default;

        std::unique_ptr<Entity> createEntity();
        void registerObject(std::shared_ptr<RObject> drawable);
        void registerCamera(std::shared_ptr<Renderer::Camera> camera);

        void onUpdate(const Core::TimeStep& timestep);
        void onDraw();

        void load();
        void unload();

    private:
        friend class Entity;

        entt::registry mRegistry;
        std::vector<std::shared_ptr<RObject>> mObjects;
        std::shared_ptr<Renderer::Camera> mCamera;
    };
} // namespace Rum::Scene
