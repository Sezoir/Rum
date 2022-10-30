#pragma once
// External dependencies
#include <glm/glm.hpp>
// Project files
#include "Scene/RObject.hpp"

namespace Rum::Renderer
{
    class Camera : public Scene::RObject
    {
    public:
        const glm::mat4& getProjection() const
        {
            return mProjection;
        };

        const glm::mat4& getView() const
        {
            return mView;
        }

        virtual void updateProjection() = 0;
        virtual void updateView() = 0;

    protected:
        Camera() = default;
        ~Camera() = default;
        glm::mat4 mProjection;
        glm::mat4 mView;
    };
} // namespace Rum::Renderer