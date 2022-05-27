#include "Scene.hpp"
#include "Entity.hpp"

namespace Rum::Scene
{
    std::unique_ptr<Entity> Scene::createEntity()
    {
        return std::make_unique<Entity>(*this, mRegistry.create());
    }

    void Scene::registerObject(std::shared_ptr<RObject> object)
    {
        mObjects.push_back(object);
    }

    void Scene::onUpdate(const Core::TimeStep& timestep)
    {
        for(auto& object : mObjects)
        {
            object->update(timestep);
        }
    }

    void Scene::onDraw()
    {
        for(auto& object : mObjects)
        {
            object->draw();
        }
    }

    void Scene::load()
    {
        for(auto& object : mObjects)
        {
            object->load();
        }
    }

    void Scene::unload()
    {
        for(auto& object : mObjects)
        {
            object->unload();
        }
    }
} // namespace Rum::Scene