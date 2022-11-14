#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Renderer/UniformBuffer.hpp"

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

    void Scene::registerCamera(std::shared_ptr<Renderer::Camera> camera)
    {
        if(camera == nullptr)
        {
            RUM_CORE_ERROR("Scene was given a nullptr when registering a camera.");
            return;
        }
        mCamera = camera;
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
        auto view = mRegistry.view<TransformationComponent, MeshComponent>();
        auto transformationBuffer = Renderer::UniformBuffer::create(sizeof(TransformationComponent));
        for(auto [entity, transformation, mesh] : view.each())
        {
            transformationBuffer->setData(&transformation);
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