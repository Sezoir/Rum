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
    void Scene::onDraw()
    {
        for(auto& object : mObjects)
        {
            object->draw();
        }
    }

    void Scene::onUpdate(const TimeStep& timestep)
    {
        for(auto& object : mObjects)
        {
            object->update(timestep);
        }
    }
} // namespace Rum::Scene